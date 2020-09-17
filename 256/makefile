CC=hc386
CFLAGS = -I..\common
LDFLAGS = -nomap

all: fa.exp

fa.exp: fa.obj ..\common\palette.obj ..\common\common.obj
	$(CC) $(LDFLAGS) -o $@ $#

clean:
	del ..\common\*.obj
	del *.obj
	del *.exp

.c.obj:
	$(CC) $(CFLAGS) -c $< -o $@
