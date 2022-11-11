CC = gcc

# shell headers, code, and targets
INC=src/include
CPPFLAGS=src/lib
OBJDIR=build/dist

# commands code and libs
CMDIR=src/code
BINDIR=build/bin

objects = $(addprefix $(OBJDIR)/, basic.o internal.o env.o shell.o)
cmds = $(addprefix $(BINDIR)/, echo hello ls)


CFLAGS = -I$(CPPFLAGS)
LDFLAGS = -L$(OBJDIR) -lreadline # -Lbuild/dist

shell: $(objects)
	$(CC) $(objects) $(LDFLAGS) -o ./build/shell

$(OBJDIR)/%.o: $(CPPFLAGS)/%.c
	$(CC) $(CFLAGS) -I$(INC) -c -o $@ $<

$(BINDIR)/%: $(CMDIR)/%.c
	$(CC) -o $@ $<

commands: $(cmds)

.PRECIOUS: %.o
