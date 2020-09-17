CC=hc386
CFLAGS = -I..\common
LDFLAGS = -nomap

all: cen0.exp cen1.exp haj.exp lo.exp

cen0.exp: cen0.obj ..\common\common.obj
	$(CC) $(LDFLAGS) -o $@ $#

cen1.exp: cen1.obj ..\common\common.obj
	$(CC) $(LDFLAGS) -o $@ $#

haj.exp: haj.obj ..\common\common.obj
	$(CC) $(LDFLAGS) -o $@ $#

lo.exp: lo.obj ..\common\common.obj
	$(CC) $(LDFLAGS) -o $@ $#

clean:
	del ..\common\*.obj
	del *.obj
	del *.exp

.c.obj:
	$(CC) $(CFLAGS) -c $< -o $@
