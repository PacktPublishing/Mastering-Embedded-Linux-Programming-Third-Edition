#! /bin/sh
### BEGIN INIT INFO
# Provides:          ondemand
# Required-Start:    $remote_fs $all
# Required-Stop:
# Default-Start:     2 3 4 5
# Default-Stop:
# Short-Description: Set the CPU Frequency Scaling governor to "ondemand"
### END INIT INFO

# Don't run if we're going to start an Android LXC container:
[ ! -f /etc/init/lxc-android-config.conf ] || exit 0

PATH=/sbin:/usr/sbin:/bin:/usr/bin

. /lib/init/vars.sh
. /lib/lsb/init-functions

AVAILABLE="/sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors"
DOWN_FACTOR="/sys/devices/system/cpu/cpufreq/ondemand/sampling_down_factor"

case "$1" in
    start)
    	start-stop-daemon --start --background --exec /etc/init.d/ondemand -- background
        ;;
    background)
	sleep 60 # probably enough time for desktop login

	[ -f $AVAILABLE ] || exit 0
	read governors < $AVAILABLE
	case $governors in
		*interactive*)
			GOVERNOR="interactive"
			break
			;;
		*ondemand*)
			GOVERNOR="ondemand"
			case $(uname -m) in
				ppc64*)
					SAMPLING=100
				;;
			esac
			break
			;;
		*powersave*)
			GOVERNOR="powersave"
			break
			;;
		*)
			exit 0
			;;
	esac

	for CPUFREQ in /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
	do
		[ -f $CPUFREQ ] || continue
		echo -n $GOVERNOR > $CPUFREQ
	done
	if [ -n "$SAMPLING" ] && [ -f $DOWN_FACTOR ]; then
		echo -n $SAMPLING > $DOWN_FACTOR
	fi
	;;
    restart|reload|force-reload)
        echo "Error: argument '$1' not supported" >&2
        exit 3
        ;;
    stop)
        ;;
    *)
        echo "Usage: $0 start|stop" >&2
        exit 3
        ;;
esac
