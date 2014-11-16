AM_LDFLAGS = @auto_import_flags@

AM_CPPFLAGS =					\
	-I$(top_srcdir)				\
	-I$(top_srcdir)/poppler

noinst_PROGRAMS = pdf-fullrewrite

if BUILD_GTK_TEST
noinst_PROGRAMS += gtk-test
if BUILD_CAIRO_OUTPUT
noinst_PROGRAMS += pdf_inspector
endif
endif

if BUILD_SPLASH_OUTPUT
noinst_PROGRAMS += perf-test
endif

gtk_test_SOURCES =					\
	gtk-test.cc

gtk_test_CPPFLAGS =					\
	$(AM_CPPFLAGS)					\
	-I$(top_srcdir)/glib				\
	-I$(top_builddir)/glib				\
	$(GTK_TEST_CFLAGS)

gtk_test_LDADD =					\
	$(top_builddir)/poppler/libpoppler.la           \
	$(top_builddir)/glib/libpoppler-glib.la         \
	$(GTK_TEST_LIBS)				\
	$(PTHREAD_LIBS)

pdf_inspector_SOURCES =					\
	pdf-inspector.cc

pdf_inspector_CPPFLAGS =				\
	$(AM_CPPFLAGS)					\
	$(GTK_TEST_CFLAGS)

pdf_inspector_LDADD =					\
	$(top_builddir)/poppler/libpoppler-cairo.la	\
	$(top_builddir)/poppler/libpoppler.la		\
	$(GTK_TEST_LIBS)				\
	$(X_EXTRA_LIBS)					\
	$(PTHREAD_LIBS)

perf_test_SOURCES =					\
	perf-test.cc					\
	perf-test-preview-dummy.cc

perf_test_LDADD =				\
	$(top_builddir)/poppler/libpoppler.la	\
	$(FREETYPE_LIBS)					\
	$(X_EXTRA_LIBS)

pdf_fullrewrite_SOURCES =				\
	pdf-fullrewrite.cc

pdf_fullrewrite_LDADD =					\
	$(top_builddir)/utils/libparseargs.la		\
	$(top_builddir)/poppler/libpoppler.la

EXTRA_DIST =					\
	pdf-operators.c				\
	pdf-inspector.ui
