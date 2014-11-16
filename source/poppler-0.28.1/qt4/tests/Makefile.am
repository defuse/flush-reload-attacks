AM_LDFLAGS = @auto_import_flags@

AM_CPPFLAGS =					\
	-I$(top_srcdir)				\
	-I$(top_srcdir)/poppler			\
	-I$(top_srcdir)/qt4/src			\
	-DTESTDATADIR=\"$(TESTDATADIR)\"        \
	$(POPPLER_QT4_CFLAGS)

LDADD =							\
	$(top_builddir)/poppler/libpoppler.la		\
	$(top_builddir)/qt4/src/libpoppler-qt4.la	\
	$(POPPLER_QT4_LIBS)

noinst_PROGRAMS = test-poppler-qt4 stress-poppler-qt4 \
	poppler-fonts test-password-qt4 stress-poppler-dir \
	poppler-attachments poppler-texts poppler-forms \
	stress-threads-qt4 test-render-to-file

test_poppler_qt4_SOURCES =			\
       test-poppler-qt4.cpp

test_render_to_file_SOURCES =			\
       test-render-to-file.cpp

test_password_qt4_SOURCES =			\
       test-password-qt4.cpp

poppler_fonts_SOURCES =				\
       poppler-fonts.cpp

poppler_attachments_SOURCES =			\
       poppler-attachments.cpp

poppler_texts_SOURCES =				\
       poppler-texts.cpp

poppler_forms_SOURCES =				\
       poppler-forms.cpp

stress_poppler_qt4_SOURCES =			\
       stress-poppler-qt4.cpp

stress_poppler_dir_SOURCES =			\
       stress-poppler-dir.cpp

stress_threads_qt4_SOURCES =			\
       stress-threads-qt4.cpp

if BUILD_POPPLER_QT4
TESTS = \
	check_attachments	\
	check_actualtext	\
	check_dateConversion	\
	check_fonts		\
	check_links		\
	check_metadata		\
	check_optcontent	\
	check_permissions	\
	check_pagelabelinfo	\
	check_pagemode		\
	check_password		\
	check_pagelayout	\
	check_search		\
	check_strings		\
	check_lexer		\
	check_goostring

check_PROGRAMS = $(TESTS)

check_attachments_SOURCES = check_attachments.cpp
check_attachments.$(OBJEXT): check_attachments.moc
check_attachments_LDADD = $(LDADD) $(POPPLER_QT4_TEST_LIBS)

check_actualtext_SOURCES = check_actualtext.cpp
check_actualtext.$(OBJEXT): check_actualtext.moc
check_actualtext_LDADD = $(LDADD) $(POPPLER_QT4_TEST_LIBS)

check_dateConversion_SOURCES = check_dateConversion.cpp
check_dateConversion.$(OBJEXT): check_dateConversion.moc
check_dateConversion_LDADD = $(LDADD) $(POPPLER_QT4_TEST_LIBS)

check_fonts_SOURCES = check_fonts.cpp
check_fonts.$(OBJEXT): check_fonts.moc
check_fonts_LDADD = $(LDADD) $(POPPLER_QT4_TEST_LIBS)

check_links_SOURCES = check_links.cpp
check_links.$(OBJEXT): check_links.moc
check_links_LDADD = $(LDADD) $(POPPLER_QT4_TEST_LIBS)

check_metadata_SOURCES = check_metadata.cpp
check_metadata.$(OBJEXT): check_metadata.moc
check_metadata_LDADD = $(LDADD) $(POPPLER_QT4_TEST_LIBS)

check_optcontent_SOURCES = check_optcontent.cpp
check_optcontent.$(OBJEXT): check_optcontent.moc
check_optcontent_LDADD = $(LDADD) $(POPPLER_QT4_TEST_LIBS)

check_pagemode_SOURCES = check_pagemode.cpp
check_pagemode.$(OBJEXT): check_pagemode.moc
check_pagemode_LDADD = $(LDADD) $(POPPLER_QT4_TEST_LIBS)

check_permissions_SOURCES = check_permissions.cpp
check_permissions.$(OBJEXT): check_permissions.moc
check_permissions_LDADD = $(LDADD) $(POPPLER_QT4_TEST_LIBS)

check_pagelayout_SOURCES = check_pagelayout.cpp
check_pagelayout.$(OBJEXT): check_pagelayout.moc
check_pagelayout_LDADD = $(LDADD) $(POPPLER_QT4_TEST_LIBS)

check_password_SOURCES = check_password.cpp
check_password.$(OBJEXT): check_password.moc
check_password_LDADD = $(LDADD) $(POPPLER_QT4_TEST_LIBS)

check_search_SOURCES = check_search.cpp
check_search.$(OBJEXT): check_search.moc
check_search_LDADD = $(LDADD) $(POPPLER_QT4_TEST_LIBS)

check_strings_SOURCES = check_strings.cpp
check_strings.$(OBJEXT): check_strings.moc
check_strings_LDADD = $(LDADD) $(POPPLER_QT4_TEST_LIBS)

check_lexer_SOURCES = check_lexer.cpp
check_lexer.$(OBJEXT): check_lexer.moc
check_lexer_LDADD = $(LDADD) $(POPPLER_QT4_TEST_LIBS)

check_pagelabelinfo_SOURCES = check_pagelabelinfo.cpp
check_pagelabelinfo.$(OBJEXT): check_pagelabelinfo.moc
check_pagelabelinfo_LDADD = $(LDADD) $(POPPLER_QT4_TEST_LIBS)

check_goostring_SOURCES = check_goostring.cpp
check_goostring.$(OBJEXT): check_goostring.moc
check_goostring_LDADD = $(LDADD) $(POPPLER_QT4_TEST_LIBS)
endif

.cpp.moc:
	$(AM_V_GEN) $(MOCQT4) -i $< -o $@
SUFFIXES: .moc

clean-generic:
	rm -f *.moc
