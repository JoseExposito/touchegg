#
# Regular cron jobs for the touchegg-gui package
#
0 4	* * *	root	[ -x /usr/bin/touchegg-gui_maintenance ] && /usr/bin/touchegg-gui_maintenance
