rtime: main.o engine.o dice.o character.o screens.o monster.o object.o map.o log.o rtutil.o
		gcc -g -lncurses -o rtime main.o engine.o dice.o character.o rtutil.o\
		screens.o monster.o object.o map.o log.o

main.o: main.c engine.h object.h map.h rtutil.h log.h character.h
		gcc -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c main.c

engine.o: engine.c engine.h
		gcc -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c engine.c

dice.o: dice.c dice.h
		gcc -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c dice.c

character.o: character.c character.h engine.h object.h
		gcc -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c character.c

screens.o: screens.c screens.h character.h engine.h
		gcc -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c screens.c

monster.o: monster.c monster.h
		gcc -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c monster.c

object.o: object.c object.h engine.h character.h
		gcc -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c object.c

map.o: map.c map.h engine.h object.h log.h
		gcc -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c map.c

rtutil.o: rtutil.c rtutil.h
		gcc -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c rtutil.c

log.o: log.h log.c engine.h rtutil.h
		gcc -g -W -Wunused -Wreturn-type -Wswitch -Wformat  -c log.c

clean:
		rm -f rtime main.o log.o engine.o dice.o character.o screens.o monster.o \
		object.o map.o rtutil.o core rt.log *~ *tdd
