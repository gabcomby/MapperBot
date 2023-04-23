# Nom du microcontroleur cible
# (exemple: 'at90s8515')
MCU=atmega324pa
# Niveau d'optimization
# Utilisez s (size opt), 1, 2, 3 ou 0 (off)
OPTLEVEL=s

# Flags pour le compilateur en C
CFLAGS=-I. -I/usr/include/simavr  -MMD -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-std=c++14 -fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall              \
	-DF_CPU=8000000UL                          

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions  

#LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)

src = $(wildcard *.cpp) 
obj = $(src:.cpp=.o)
trg = librobot1618.a

all: CFLAGS += -DF_CPU=8000000UL
all: CXXFLAGS += -DF_CPU=8000000UL
all: $(trg)
$(trg): $(obj)
	avr-ar -crs $(trg) $(obj)
%.o:%.cpp
	avr-gcc $(CFLAGS) $(CXXFLAGS) -c -o $@ $<
clean:
	rm -f *.o
	rm -f *.a
	rm -f *.d


