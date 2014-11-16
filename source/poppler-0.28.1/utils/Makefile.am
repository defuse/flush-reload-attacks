AM_LDFLAGS = @auto_import_flags@

AM_CPPFLAGS =					\
	-I$(top_srcdir)				\
	-I$(top_srcdir)/goo			\
	-I$(top_srcdir)/utils			\
	-I$(top_srcdir)/poppler			\
	$(UTILS_CFLAGS)

LDADD =						\
	libparseargs.la				\
	$(top_builddir)/poppler/libpoppler.la	\
	$(UTILS_LIBS)

if BUILD_UTILS

bin_PROGRAMS =					\
	pdfdetach				\
	pdffonts				\
	pdfimages				\
	pdfinfo					\
	pdftops					\
	pdftotext				\
	pdftohtml				\
	pdfseparate				\
	pdfunite

if BUILD_SPLASH_OUTPUT
bin_PROGRAMS += pdftoppm
endif

if BUILD_CAIRO_OUTPUT
bin_PROGRAMS += pdftocairo
endif

dist_man1_MANS =				\
	pdfdetach.1				\
	pdffonts.1				\
	pdfimages.1				\
	pdfinfo.1				\
	pdftops.1				\
	pdftotext.1				\
	pdftohtml.1				\
	pdfseparate.1				\
	pdfunite.1

if BUILD_SPLASH_OUTPUT
dist_man1_MANS += pdftoppm.1
endif

if BUILD_CAIRO_OUTPUT
dist_man1_MANS += pdftocairo.1
endif

endif # if BUILD_UTILS

pdfdetach_SOURCES =				\
	pdfdetach.cc

pdffonts_SOURCES =				\
	pdffonts.cc

pdfimages_SOURCES =				\
	pdfimages.cc				\
	ImageOutputDev.cc			\
	ImageOutputDev.h			\
	JSInfo.cc				\
	JSInfo.h

pdfinfo_SOURCES =				\
	pdfinfo.cc				\
	printencodings.cc			\
	printencodings.h			\
	JSInfo.cc				\
	JSInfo.h

pdftops_SOURCES =				\
	pdftops.cc

pdftotext_SOURCES =				\
	pdftotext.cc				\
	printencodings.cc			\
	printencodings.h

pdftohtml_SOURCES =				\
	pdftohtml.cc				\
	HtmlFonts.cc				\
	HtmlFonts.h				\
	HtmlLinks.cc				\
	HtmlLinks.h				\
	HtmlOutputDev.cc			\
	HtmlOutputDev.h				\
	HtmlUtils.h

# HtmlOutputDev uses goo/PNGWriter.h that may depend on libpng header
if BUILD_LIBPNG
pdftohtml_CXXFLAGS = $(AM_CXXFLAGS) $(LIBPNG_CFLAGS)
endif

pdfseparate_SOURCES =				\
	pdfseparate.cc

pdfunite_SOURCES =				\
	pdfunite.cc

pdftoppm_SOURCES =				\
	pdftoppm.cc

pdftocairo_SOURCES =				\
	pdftocairo.cc				\
	pdftocairo-win32.cc			\
	pdftocairo-win32.h

if BUILD_CAIRO_OUTPUT
if USE_CMS
PDFTOCAIRO_CFLAGS += $(LCMS_CFLAGS)
PDFTOCAIRO_LIBS += $(LCMS_LIBS)
endif
endif

pdftocairo_LDADD =					\
	$(top_builddir)/poppler/libpoppler-cairo.la	\
	$(LDADD)					\
	$(PDFTOCAIRO_LIBS)				\
	$(PTHREAD_LIBS)

pdftocairo_CPPFLAGS =				\
	$(AM_CPPFLAGS)				\
	$(PDFTOCAIRO_CFLAGS)

noinst_LTLIBRARIES = libparseargs.la

libparseargs_la_SOURCES =			\
	parseargs.cc				\
	parseargs.h

# Yay, automake!  It should be able to figure out that it has to dist
# pdftoppm.1, but nooo.  So we just add it here.

EXTRA_DIST = pdf2xml.dtd pdftoppm.1
