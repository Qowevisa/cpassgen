include config.mk
project_name = cpassgen
libs = bit gen math random
OBJ_F = obj
SRC_F = src

def: build
	@

$(OBJ_F)/%.o : $(SRC_F)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

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
