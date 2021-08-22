#ifndef BASE_HPP
#define BASE_HPP

#define PRINT_VALID (int)configFlags == (int)SCARLET_ENABLE_LOGGER ||\ 
                             (int)configFlags == (int)SCARLET_DISABLE_FILE_OUTPUT ||\ 
                             (int)configFlags == (int)(SCARLET_ENABLE_LOGGER | SCARLET_ENABLE_FILE_OUTPUT)

#define STORE_VALID (int)configFlags == (int)(SCARLET_ENABLE_LOGGER | SCARLET_ENABLE_FILE_OUTPUT)

#endif