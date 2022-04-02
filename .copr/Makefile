outdir  ?= $(HOME)/rpmbuild

.PHONY: srpm
srpm:
	dnf install -y git
	mkdir -p $(outdir)/{RPMS,SRPMS,BUILD,SOURCES,SPECS}
	tar -czvf $(outdir)/SOURCES/touchegg.tar.gz -C .. touchegg --transform s/^touchegg/touchegg-$$(git describe --tags --abbrev=0)/
	rpmbuild -D'_topdir $(outdir)' -D'_srcrpmdir $(outdir)' -bs rpm/touchegg.spec
