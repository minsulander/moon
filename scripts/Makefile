# NOTE: This is a makefile full of utilities.
# The real build uses CMake.

OS=$(shell uname -s | tr A-Z a-z | sed -e 's/darwin/mac/' | sed -e 's/mingw32_nt.*/mingw/')
ARCH=$(shell uname -m)
PATH := ../bin:$(PATH)
DATE=$(shell date +%Y%m%d)
BUILD=../build-$(OS)-$(ARCH)
DEPDIR=../moon-dependencies-$(OS)-$(ARCH)
DIST_DEV=../moon-$(OS)-$(ARCH)-dev
DIST_DEV_ARCHIVE=../moon-$(OS)-$(ARCH)-dev.tar.bz2
APPBUNDLE_NAME=../moon
APPBUNDLE=$(APPBUNDLE_NAME).app
XCODEBUILD=../xcode-$(ARCH)
XCODEPROJ=$(XCODEBUILD)/moon.xcodeproj

.PHONY: config build test testreport clean all

all: build

config: $(BUILD)/Makefile

$(DEPDIR)/.depsdone $(BUILD)/Makefile:
	@bash configure
	
$(BUILD)/bin/moontest $(BUILD)/bin/moonshell:$(DEPDIR)/.depsdone
	$(MAKE) -C $(BUILD)

	
build: $(BUILD)/bin/moonshell
	
test: $(BUILD)/bin/moontest
	$(MAKE) -C $(BUILD) test

testreport: test
	cat $(BUILD)/Testing/Temporary/LastTest.log
	
clean:
	$(MAKE) -C $(BUILD) clean
	
distclean:
	rm -rf $(BUILD)
	rm -rf $(DIST_DEV) $(DIST_DEV_ARCHIVE)

# Source files used to generate Wiki documentation
WIKI_DOC_FILES = \
	../docs/mediawiki/fileref_head.mediawiki \
	../src/moon/Scenario.cpp \
	../src/moon/Environment.cpp \
	../src/moon/ControlHandler.cpp \
	../src/moon/Configuration.cpp \
	../src/moodyn/World.cpp \
	../docs/mediawiki/fileref_objects.mediawiki \
	../src/moon/objects/BaseObject.cpp \
	../src/moon/objects/TransformObject.cpp \
	../src/moon/objects/VisualObject.cpp \
	../src/moon/objects/KinematicObject.cpp \
	../src/moon/objects/Camera.cpp \
	../src/moon/objects/Light.cpp \
	../src/moon/objects/SkyDome.cpp \
	../src/moon/objects/VegetationLayer.cpp \
	../src/moodyn/objects/PhysicalObject.cpp \
	../src/moodyn/objects/DynamicPhysicalObject.cpp \
	../docs/mediawiki/fileref_components.mediawiki \
	../src/moon/components/Component.cpp \
	../src/moon/components/VisualModel.cpp \
	../src/moon/components/TexturePlane.cpp \
	../src/moon/components/Instrument.cpp \
	../src/moon/components/Script.cpp \
	../src/moon/components/MotionModel.cpp \
	../src/moon/components/SimpleMotion.cpp \
	../src/moodyn/components/Geometry.cpp \
	../src/moodyn/components/Body.cpp \
	../src/moodyn/components/Joint.cpp \
	../src/moodyn/components/Explosion.cpp \
	../src/moodyn/components/ContinuousForce.cpp \
	../src/moodyn/components/ControlForce.cpp \
	../src/moodyn/components/Drag.cpp \
	../src/moodyn/components/PIDController.cpp \
	../src/moodyn/Atmosphere.cpp \
	../src/maudio/Sound.cpp \
	../src/maudio/Source.cpp \
	../src/maudio/SingleSource.cpp \
	../src/maudio/ToneSource.cpp \
	../docs/mediawiki/fileref_other.mediawiki \
	../src/moon/Modifier.cpp \
	../docs/mediawiki/fileref_examples.mediawiki \
	../data/examples/smallest_possible.xml \
	../data/examples/kinematic.xml \
	../data/examples/scripted_object.xml \
	../data/examples/dynamics_bounce.xml \
	../docs/mediawiki/fileref_foot.mediawiki

wikidocs:
	./extract_wiki_docs $(WIKI_DOC_FILES) >../docs/mediawiki/moon-fileref.mediawiki
	cat ../docs/mediawiki/moon-fileref.mediawiki | ./wiki2html >../docs/moon-fileref.html

../docs/dependencies/tagfiles/osg.xml:
	cd ../docs/dependencies && mkdir -p tagfiles && doxytag -t tagfiles/osg.xml OpenSceneGraphReferenceDocs
	
../docs/dependencies/tagfiles/openthreads.xml:
	cd ../docs/dependencies && mkdir -p tagfiles && doxytag -t tagfiles/openthreads.xml OpenThreadsReferenceDocs
	
../docs/dependencies/tagfiles/tinyxml.xml:
	cd ../docs/dependencies && mkdir -p tagfiles && doxytag -t tagfiles/tinyxml.xml TinyXML

../docs/dependencies/tagfiles/raknet.xml:
	cd ../docs/dependencies && mkdir -p tagfiles && doxytag -t tagfiles/raknet.xml RakNet/Doxygen/html
	
doxygen: ../docs/dependencies/tagfiles/osg.xml ../docs/dependencies/tagfiles/openthreads.xml ../docs/dependencies/tagfiles/tinyxml.xml ../docs/dependencies/tagfiles/raknet.xml
	cd ../docs && doxygen

docs: wikidocs doxygen

.PHONY: wikidocs doxygen docs




$(DIST_DEV)/.depsdone: $(DEPDIR)/.depsdone
	mkdir -p $(DIST_DEV)
	tar cf - -C $(DEPDIR) . | ( cd $(PWD)/$(DIST_DEV) ; tar xf - )

# TODO dependency on moon library - something else?
$(DIST_DEV)/.installdone: $(DIST_DEV)/.depsdone $(BUILD)/bin/moonshell
	bash configure -DCMAKE_INSTALL_PREFIX=$(PWD)/$(DIST_DEV)
	make -C $(BUILD) install
	tar cf - -C .. -X install_exclude_dev.txt `cat install_files_dev.txt` | ( cd $(DIST_DEV) ; tar xf - )
	find $(DIST_DEV) -name '*~' -delete
	touch $(DIST_DEV)/.installdone
# TODO readme, license file, fix install names on OSX, some environment script

$(DIST_DEV_ARCHIVE): $(DIST_DEV)/.installdone
	tar cfj $(DIST_DEV_ARCHIVE) $(DIST_DEV)

install-dist-dev-deps: $(DIST_DEV)/.depsdone
install-dist-dev: $(DIST_DEV)/.installdone
dist-dev: $(DIST_DEV_ARCHIVE)
.PHONY: install-dist-dev-deps install-dist-dev dist-dev

ifeq ($(OS),mac)

xcode: $(XCODEPROJ)
.PHONY: xcode

$(XCODEPROJ): $(DEPDIR)/.depsdone $(DEPDIR)/bin/cmake
	mkdir -p $(XCODEBUILD)
	cd $(XCODEBUILD) && $(DEPDIR)/bin/cmake -G Xcode ..
	
xbuild: $(XCODEBUILD)/bin/Debug/moonshell
.PHONY: xbuild

$(XCODEBUILD)/bin/Debug/moonshell $(XCODEBUILD)/bin/Debug/moontest:
	cd $(XCODEBUILD) && $(DEPDIR)/bin/cmakexbuild

xtest: $(XCODEBUILD)/bin/Debug/moontest
	cd $(XCODEBUILD) && $(DEPDIR)/bin/ctest 	
.PHONY: xtest

appbundle: $(APPBUNDLE)
.PHONY: appbundle

$(APPBUNDLE): $(DEPDIR)/.depsdone $(BUILD)/bin/moonshell $(wildcard $(BUILD)/lib/*) $(wildcard $(BUILD)/lib/moonPlugins/*.so)
	mac/mkAppBundle mac/start.sh --name=$(APPBUNDLE_NAME) --icon=mac/moon-icon.icns --plist=mac/Info.plist-app-with-drag-n-drop\
		$(BUILD)/bin/moonshell \
		$(BUILD)/lib \
		../data
	cp -rfp $(DEPDIR)/lib/osgPlugins-* $(APPBUNDLE)/Contents/Resources/lib/
	./copylibs $(DEPDIR)/lib $(APPBUNDLE)/Contents/Resources/lib $(APPBUNDLE)/Contents/Resources/moonshell
	./copylibs $(DEPDIR)/lib $(APPBUNDLE)/Contents/Resources/lib $(APPBUNDLE)/Contents/Resources/lib/*.dylib
	./copylibs $(DEPDIR)/lib $(APPBUNDLE)/Contents/Resources/lib $(APPBUNDLE)/Contents/Resources/lib/*Plugins*/*.so
	mac/fix_install_names $(APPBUNDLE)/Contents/Resources/lib lib \
		$(APPBUNDLE)/Contents/Resources/moonshell \
		$(APPBUNDLE)/Contents/Resources/lib/*.dylib \
		$(APPBUNDLE)/Contents/Resources/lib/osgPlugins-*/*.so \
		$(APPBUNDLE)/Contents/Resources/lib/moonPlugins/*.so
	rm -rf `find $(APPBUNDLE) -name .svn`
	find $(APPBUNDLE) -name '*~' -delete
	@du -sh $(APPBUNDLE)
	
.PHONY: appbundle-update
appbundle-update: $(BUILD)/bin/moonshell $(wildcard $(BUILD)/lib/*.dylib) $(wildcard $(BUILD)/lib/moonPlugins/*.so)
	cp -f $(BUILD)/bin/moonshell $(APPBUNDLE)/Contents/Resources/moonshell
	cp -f $(BUILD)/lib/*.dylib $(APPBUNDLE)/Contents/Resources/lib/
	cp -f $(BUILD)/lib/moonPlugins/*.so $(APPBUNDLE)/Contents/Resources/lib/moonPlugins/
	mac/fix_install_names $(APPBUNDLE)/Contents/Resources/lib lib \
		$(APPBUNDLE)/Contents/Resources/moonshell \
		$(APPBUNDLE)/Contents/Resources/lib/*.dylib \
		$(APPBUNDLE)/Contents/Resources/lib/moonPlugins/*.so
	
# TODO remove osxstarter	
mac/osxstarter: mac/osxstarter.cpp
	g++ $^ -o $@ -I../include -L../lib -lfltk -framework Carbon -framework ApplicationServices

# TODO renew and remove	
moon.app: mac/osxstarter ../bin/moonshell mac/moon-icon.icns mac/Info.plist-app-with-drag-n-drop mac/start.sh
	mac/mkAppBundle mac/osxstarter --name=moon --icon=mac/moon-icon.icns --plist=mac/Info.plist-app-with-drag-n-drop mac/start.sh ../bin ../lib ../data

moon-mac-$(DATE).dmg: test moon.app docs
	if [ -e dmg ]; then rm -rf dmg; fi
	if [ -e moon-mac-$(DATE).dmg ]; then rm -f moon-mac-$(DATE).dmg; fi
	mkdir dmg
	cp -rf moon.app dmg/
	cp -rf ../docs dmg/
	rm -rf `find dmg -name .svn`
	find dmg -name '*~' -delete
	rm -f dmg/docs/Doxyfile
	/Developer/Tools/SetFile -c '????' dmg/docs/*.html
	hdiutil create -srcfolder dmg -volname moon-$(DATE) -format UDBZ $@

endif