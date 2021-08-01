include config.mk
project_name = cpassgen

options:
	@printf $(project_name)" make menu:"
	@printf "make [options]   :: print this menu\n"
	@printf "make build       :: compile\n"
	@printf "make install     :: copys to bin folder\n"
	@printf "make clean       :: remove *.o files\n"
	@printf "make full        :: equvalent to \"make build && make install && make clean\"\n\033[0;0m"

build: 
	@echo "Bulding..."
	$(CC) -o $(project_name) $(project_name).c

install:
	@echo "Copying to bin folder..."
	sudo cp $(project_name) $(usr_bin_folder_path)

clean: 
	@echo "Removing executable file from folder"
	-rm $(project_name) 2> /dev/null

full: build install clean

.PHONY: options libs build install clean full
