include config.mk
project_name = cpassgen
libs = math bit
OBJ_F = obj
SRC_F = src

options:
	@printf $(project_name)" make menu:\n"
	@printf "make [options]   ::print this menu\n"
	@printf "make build       ::compile\n"
	@printf "make install     ::copies to bin folder\n"
	@printf "make clean       ::remove *.o files\n"
	@printf "make full        ::equvalent to \"make build && make install && make clean\"\n\033[0;0m"

$(OBJ_F)/%.o : $(SRC_F)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

libs: 
	@echo "Compile libs files :: " $(libs)

build: $(libs:%=$(OBJ_F)/%.o)
	@echo "Bulding..."
	$(CC) -o $(project_name) $(SRC_F)/$(project_name).c $(libs:%=$(OBJ_F)/%.o) $(CFLAGS)

install:
	@echo "Copying to bin folder..."
	sudo cp $(project_name) $(usr_bin_folder_path)

clean: 
	@echo "Removing libs files ::"
	-rm $(OBJ)/*.o 2> /dev/null
	@echo "Removing executable file from folder"
	-rm $(project_name) 2> /dev/null

full: build install clean

.PHONY: options libs build install clean full
