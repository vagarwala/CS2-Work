import string
def freq(s):
	alphabet = string.ascii_lowercase
	freqs = []
	for letter in alphabet:
		freqs.append(s.count(letter) + s.count(letter.upper()))
	return freqs

s = raw_input()
print freq(s)