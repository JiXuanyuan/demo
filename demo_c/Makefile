VPATH	=	src:common
CC	=	gcc
CFLAGS	=	-I common #-D BATE
COMMONH	:=	common.h log.h alloc.h bool.h

main : main.o string.o kmp.o

%.o : %.c %.h $(COMMONH)
	$(CC) -c $(CFLAGS) $< -o $@
	# 编译依赖1：$?
%.o : %.c $(COMMONH)
	$(CC) -c $(CFLAGS) $< -o $@
	# 编译依赖2：$?
%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@
	# 编译依赖3：$?

.PHONY : clean
clean :
	-rm main *.o
