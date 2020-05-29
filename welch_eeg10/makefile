INCDIR=inc
SRCDIR=src
OBJDIR=obj
BINDIR=bin

BIN=$(BINDIR)/xqwelch

$(BIN):$(OBJDIR)/process.o  $(OBJDIR)/fft.o  $(OBJDIR)/main.o    
	mpicc  -Wall  -o  $@ $^  -lm

$(OBJDIR)/main.o:$(SRCDIR)/main.c inc/welch.h
	mpicc -Wall  -I$(INCDIR)  -c $< -o $@

$(OBJDIR)/process.o:$(SRCDIR)/process.c inc/welch.h
	mpicc -Wall  -I$(INCDIR)  -c $< -o $@

$(OBJDIR)/fft.o:$(SRCDIR)/fft.c inc/welch.h
	mpicc -Wall  -I$(INCDIR)  -c $< -o $@

clean:
	rm -f $(BINDIR)/* $(OBJDIR)/*

