#
# Regular cron jobs for the touchegg package
#
0 4	* * *	root	[ -x /usr/bin/touchegg_maintenance ] && /usr/bin/touchegg_maintenance
