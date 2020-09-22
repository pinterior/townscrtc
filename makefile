CC = hc386
CFLAGS = -Heol=#a -Icommon
LDFLAGS = -nomap
LIBS = $(HCDIR)\small\c_heap.obj

EXPS = \
   256\fa.exp 256\zv.exp \
   32k\fa.exp 32k\zv.exp \
   32k-32k\cen0.exp 32k-32k\cen1.exp 32k-32k\fo.exp \
   32k-32k\haj.exp 32k-32k\lo.exp

all: $(EXPS)

.c.obj:
	$(CC) $(CFLAGS) -c $< -o $@

.obj.exp:
	$(CC) $(LDFLAGS) -o $@ $# $(LIBS)

clean:
	del common\*.obj
	del 256\*.obj
	del 32k\*.obj
	del 32k-32k\*.obj
	del 256\*.exp
	del 32k\*.exp
	del 32k-32k\*.exp

256\fa.exp: common\palette.obj common\common.obj
256\zv.exp: common\palette.obj common\common.obj
32k\fa.exp: common\common.obj
32k\zv.exp: common\common.obj
32k-32k\cen0.exp: common\common.obj
32k-32k\cen1.exp: common\common.obj
32k-32k\fo.exp: common\common.obj
32k-32k\haj.exp: common\common.obj
32k-32k\lo.exp: common\common.obj

common\common.obj: common\common.h common\typ.h
common\palette.obj: common\common.h common\palette.h common\typ.h
256\fa.obj: common\common.h common\palette.h common\typ.h common\settings.h
256\zv.obj: common\common.h common\palette.h common\typ.h common\settings.h
32k\fa.obj: common\common.h common\typ.h common\settings.h
32k\zv.obj: common\common.h common\typ.h common\settings.h
32k-32k\cen0.obj: common\common.h common\typ.h common\settings.h
32k-32k\cen1.obj: common\common.h common\typ.h common\settings.h
32k-32k\fo.obj: common\common.h common\typ.h common\settings.h
32k-32k\haj.obj: common\common.h common\typ.h common\settings.h
32k-32k\lo.obj: common\common.h common\typ.h common\settings.h
