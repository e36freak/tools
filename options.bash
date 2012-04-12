#!/bin/bash

# this is how i manually parse options for complex shell scripts. the original
# loop, even though it uses 'optstring', will NOT check if an option that takes
# a required argument has said argument provided. that must be done within the
# second loop and case statement, yourself. Its purpose is solely to determine
# that -oARG is split into -o ARG, and not -o -A -R -G.

################################################################################

# option string, for short options.
# very much like getopts, any option followed by a ':' takes a required arg
optstring=h

# iterate over options, breaking -ab into -a -b and --foo=bar into --foo bar
# also turns -- into --endopts to avoid issues with things like '-o-', the '-'
# should not indicate the end of options, but be an invalid option (or the
# argument to the option, such as wget -qO-)
unset options
while (($#)); do
  case $1 in
    # if option is of type -ab
    -[!-]?*)
      # loop over each character starting with the second
      for ((i=1; i<${#1}; i++)); do
        c=${1:i:1}
        
        # add current char to options
        options+=("-$c")

        # if option takes a required argument, and it's not the last char
        # make the rest of the string its argument
        if [[ $optstring = *"$c:"* && ${1:i+1} ]]; then
          options+=("${1:i+1}")
          break
        fi
      done
      ;;
    # if option is of type --foo=bar, split on first '='
    --?*=*) options+=("${1%%=*}" "${1#*=}");;
    # add --endopts for --
    --) options+=(--endopts);;
    # otherwise, nothing special
    *) options+=("$1");;
  esac

  shift
done
# set new positional parameters to altered options
set -- "${options[@]}"
unset options

# actually parse the options and do stuff
while [[ $1 = -?* ]]; do
  case $1 in
    -h|--help) usage >&2; exit 0;;
    --endopts) shift; break;;
    *) die "invalid option: $1";;
  esac

  shift
done
