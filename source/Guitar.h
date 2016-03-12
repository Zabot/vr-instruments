#ifndef GUITAR_H
#define GUITAR_H

class Guitar
{
public:
	Guitar(MidiSink &sink);
	~Guitar();

	void fret(unsigned int string, unsigned int fret);
	void pick(unsigned int string);
	void strum();

private:
	unsigned int getNote(unsigned int string, unsigned int fret);

private:
	MidiSink &sink;
	unsigned int *frets;
};

#endif
