SUBDIRS = 	en es fr el local pt zh de
DIST_SUBDIRS = 	en es fr el local pt zh de
EXTRA_DIST = aide_cas README index.html dxcas/* pari/*

dist_pkgdata_DATA = aide_cas
dist_doc_DATA = README index.html

install-exec-hook: 
	$(install_sh) -d $(DESTDIR)$(prefix)/share/giac/doc/dxcas
	$(install_sh) -d $(DESTDIR)$(prefix)/share/giac/doc/pari
	$(INSTALL_DATA) $(top_srcdir)/doc/dxcas/* $(DESTDIR)$(prefix)/share/giac/doc/dxcas
	$(INSTALL_DATA) $(top_srcdir)/doc/pari/* $(DESTDIR)$(prefix)/share/giac/doc/pari
	$(INSTALL_DATA) $(top_srcdir)/doc/index.html $(DESTDIR)$(prefix)/share/giac/doc/
	$(INSTALL_DATA) $(top_srcdir)/doc/README $(DESTDIR)$(prefix)/share/giac/doc/
	ln -sf ../aide_cas $(DESTDIR)$(prefix)/share/giac/doc/aide_cas
#	ln -sf $(DESTDIR)$(prefix)/share/giac/doc/en/cascmd_en $(DESTDIR)$(prefix)/share/giac/doc/local/cascmd_local
#	ln -sf $(DESTDIR)$(prefix)/share/giac/doc/en/casinter $(DESTDIR)$(prefix)/share/giac/doc/local/casinter
#	ln -sf $(DESTDIR)$(prefix)/share/giac/doc/en/keywords $(DESTDIR)$(prefix)/share/giac/doc/local/keywords
#	ln -sf $(DESTDIR)$(prefix)/share/giac/doc/en/xcasex $(DESTDIR)$(prefix)/share/giac/doc/local/xcasex
#	ln -sf $(DESTDIR)$(prefix)/share/giac/doc/en/xcasmenu $(DESTDIR)$(prefix)/share/giac/doc/local/xcasmenu

