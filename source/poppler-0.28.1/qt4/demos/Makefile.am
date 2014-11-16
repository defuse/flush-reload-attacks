AM_LDFLAGS = @auto_import_flags@

noinst_PROGRAMS = poppler_qt4viewer

BUILT_SOURCES =					\
	abstractinfodock.moc			\
	embeddedfiles.moc			\
	fonts.moc				\
	info.moc				\
	metadata.moc				\
	navigationtoolbar.moc			\
	optcontent.moc				\
	pageview.moc				\
	permissions.moc				\
	thumbnails.moc				\
	toc.moc					\
	viewer.moc

poppler_qt4viewer_SOURCES =			\
	abstractinfodock.cpp			\
	abstractinfodock.h			\
	documentobserver.cpp			\
	documentobserver.h			\
	embeddedfiles.cpp			\
	embeddedfiles.h				\
	fonts.cpp				\
	fonts.h					\
	info.cpp				\
	info.h					\
	main_viewer.cpp				\
	metadata.cpp				\
	metadata.h				\
	navigationtoolbar.cpp			\
	navigationtoolbar.h			\
	optcontent.cpp				\
	optcontent.h				\
	pageview.cpp				\
	pageview.h				\
	permissions.cpp				\
	permissions.h				\
	thumbnails.cpp				\
	thumbnails.h				\
	toc.cpp					\
	toc.h					\
	viewer.cpp				\
	viewer.h

poppler_qt4viewer_CPPFLAGS =			\
	-I$(top_srcdir)				\
	-I$(top_srcdir)/poppler			\
	-I$(top_srcdir)/qt4/src			\
	$(POPPLER_QT4_CFLAGS)

poppler_qt4viewer_LDADD =				\
	$(top_builddir)/poppler/libpoppler.la		\
	$(top_builddir)/qt4/src/libpoppler-qt4.la	\
	$(POPPLER_QT4_LIBS)

# This rule lets GNU make create any *.moc from the equivalent *.h
.h.moc:
	$(AM_V_GEN) $(MOCQT4) -i $< -o $@
SUFFIXES: .moc

clean-generic:
	rm -f *.moc
