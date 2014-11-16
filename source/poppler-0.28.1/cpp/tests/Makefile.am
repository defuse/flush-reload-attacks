AM_LDFLAGS = @auto_import_flags@

AM_CPPFLAGS =					\
	-I$(top_srcdir)				\
	-I$(top_srcdir)/utils			\
	-I$(top_srcdir)/cpp

LDADD =						\
	$(top_builddir)/utils/libparseargs.la	\
	$(top_builddir)/poppler/libpoppler.la	\
	$(top_builddir)/cpp/libpoppler-cpp.la

noinst_PROGRAMS =				\
	poppler-dump				\
	poppler-render

poppler_dump_SOURCES =				\
	poppler-dump.cpp

poppler_render_SOURCES =			\
	poppler-render.cpp
