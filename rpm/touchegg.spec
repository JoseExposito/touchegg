Name:           touchegg
Summary:        Multi-touch gesture recognizer
Url:            https://github.com/JoseExposito/touchegg
Version:        2.0.9
Release:        1
License:        GPLv3+
Group:          Applications/Productivity
Vendor:         José Expósito <jose.exposito89@gmail.com>
Packager:       José Expósito <jose.exposito89@gmail.com>

Autoreq:        1
Prefix:         %{_prefix}
Source0:        touchegg.tar.gz

%description
Touchégg is an app that runs in the background and transform the gestures you make in your touchpad into visible actions in your desktop.
For example, you can swipe up with 3 fingers to maximize a window or swipe left with 4 finger to switch to the next desktop.


%prep
%setup -n touchegg


%build
%cmake
%cmake_build


%install
%cmake_install


%check


%clean


%post

if [ "$1" -ge 1 ]; then
  systemctl daemon-reload
  systemctl reenable touchegg
  systemctl stop touchegg
  systemctl start touchegg
fi


%postun
%systemd_postun_with_restart touchegg.service


%pre


%preun
%systemd_preun touchegg.service


%files
%defattr(-,root,root,-)

%dir %{_datadir}/touchegg

%{_bindir}/touchegg
%{_datadir}/touchegg/touchegg.conf
%{_unitdir}/touchegg.service

%config %{_sysconfdir}/xdg/autostart/touchegg.desktop


%changelog

* Mon Apr 05 2021 José Expósito <jose.exposito89@gmail.com> - 2.0.9-1
- Use screen rotation to calculate touchscreen gestures direction

* Wed Feb 24 2021 José Expósito <jose.exposito89@gmail.com> - 2.0.8-1
- Added daily and stable PPA builds
- Fix animation when screens ot the same size are arranged vertically
- Fix crash caused by a g_variant not being referenced
- Handle the TOUCH_CANCEL event to avoid bugs
