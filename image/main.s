MAGIC:                                      # PNG magic bytes
.byte 0x89                                  # Detect transmission systems that do not support 8-bot data.  
.byte 0x50, 0x4E, 0x47                      # "PNG" in ascii letters
.byte 0x0D, 0x0A                            # DOS-style line ending
.byte 0x1A                                  # For dos command "type" to stop
.byte 0x0A                                  # Detect Unix-Dos line ending conversion ;

# IHDR
IHDR_LEN:   .byte 0, 0, 0, 13 # Length of data
IHDR_NAME:  .byte 'I', 'H', 'D', 'R'        # Chunk type/name
IHDR_DATA:                                  # Contents
.byte 0, 0, 0, 1                            # padded image width 
.byte 0, 0, 0, 1                            # padded image height
.byte 8                                     # bit depth : each pixel is an R,G,B triple.
.byte 2                                     # color type : colored
.byte 0, 0, 0                               # no compression, filter, and interlace methods
IHDR_CRC:   .byte 0x90, 0x77, 0x53, 0xDE    # just commented out the rest and used crc32 command to get this

# IDAT
IDAT_LEN:   .byte 0, 0, 0, 12               # padded length
IDAT_NAME:  .byte 'I', 'D', 'A', 'T'        # Chunk type/name
IDAT_DATA:                                  # Chunk's data
.byte 0x08, 0xD7, 0x63, 0xF8, 0xCF, 0xC0    # GIMP did most the work here
.byte 0x00, 0x00, 0x03, 0x01, 0x01, 0x00    # Apparently it requires compression and filtering
IDAT_CRC:   .byte 0x18, 0xDD, 0x8D, 0xB0    # same as IHDR_CRC

# IEND 
IEND_LEN:   .byte 0, 0, 0, 0                # there is no data
IEND_NAME:  .byte 'I', 'E', 'N', 'D'        # Name is still required
IEND_CRC:   .byte 0xAE, 0x42, 0x60, 0x82    # crc still required too I think
