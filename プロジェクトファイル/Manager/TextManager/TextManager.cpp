#include "TextManager.h"
#include <map>

/// <summary>
/// ���{��̃e�L�X�g�Ǘ�
/// </summary>
namespace TextManager
{
	//���{��\�����邽�߂̘A�z�z��
	std::map<char, int> text;

	//������
	void TextManager::Initialize()
	{
		text['��'] = 0;  text['��'] = 1; text['��'] = 2; text['��'] = 3; text['��'] = 4;
		text['��'] = 5;  text['��'] = 6; text['��'] = 7; text['��'] = 8; text['��'] = 9;
		text['��'] = 10; text['��'] = 11;text['��'] = 12;text['��'] = 13;text['��'] = 14;
		text['��'] = 15; text['��'] = 16;text['��'] = 17;text['��'] = 18;text['��'] = 19;
		text['��'] = 20; text['��'] = 21;text['��'] = 22;text['��'] = 23;text['��'] = 24;
		text['��'] = 25; text['��'] = 26;text['��'] = 27;text['��'] = 28;text['��'] = 29;
		text['��'] = 30; text['��'] = 31;text['��'] = 32;text['��'] = 33;text['��'] = 34;
		text['��'] = 35; text['��'] = 36;text['��'] = 37;
		text['��'] = 38; text['��'] = 39;text['��'] = 40;text['��'] = 41;text['��'] = 42;
		text['��'] = 43; text['��'] = 44;text['��'] = 45;
		text['��'] = 46; text['��'] = 47;text['��'] = 48;
		text['�A'] = 49; text['�C'] = 50;text['�E'] = 51;text['�G'] = 52;text['�I'] = 53;
		text['�J'] = 54; text['�L'] = 55;text['�N'] = 56;text['�P'] = 57;text['�R'] = 58;
		text['�T'] = 59; text['�V'] = 60;text['�X'] = 61;text['�Z'] = 62;text['�\'] = 63;
		text['�^'] = 64; text['�`'] = 65;text['�c'] = 66;text['�e'] = 67;text['�g'] = 68;
		text['�i'] = 69; text['�j'] = 70;text['�k'] = 71;text['�l'] = 72;text['�m'] = 73;
		text['�n'] = 74; text['�q'] = 75;text['�t'] = 76;text['�w'] = 77;text['�z'] = 78;
		text['�}'] = 79; text['�~'] = 80;text['��'] = 81;text['��'] = 82;text['��'] = 83;
		text['��'] = 84; text['��'] = 85;text['��'] = 86;
		text['��'] = 87; text['��'] = 88;text['��'] = 89;text['��'] = 90;text['��'] = 91;
		text['��'] = 92; text['��'] = 93;text['��'] = 94;
		text['��'] = 95; text['��'] = 96;text['��'] = 97;
		text['a']  = 98; text['b']  = 99;text['c'] = 100;text['d'] = 101;text['e'] = 102;
		text['f'] = 103; text['g'] = 104;text['h'] = 105;text['i'] = 106;text['j'] = 107;
		text['k'] = 108; text['l'] = 109;text['m'] = 110;text['n'] = 111;text['o'] = 112;
		text['p'] = 113; text['q'] = 114;text['r'] = 115;text['s'] = 116;text['t'] = 117;
		text['u'] = 118; text['v'] = 119;text['w'] = 120;text['x'] = 121;text['y'] = 122;
		text['z'] = 123;
		text['A'] = 124; text['B'] = 125;text['C'] = 126;text['D'] = 127;text['E'] = 128;
		text['F'] = 129; text['G'] = 130;text['H'] = 131;text['I'] = 132;text['J'] = 133;
		text['K'] = 134; text['L'] = 135;text['M'] = 136;text['N'] = 137;text['O'] = 138;
		text['P'] = 139; text['Q'] = 140;text['R'] = 141;text['S'] = 142;text['T'] = 143;
		text['U'] = 144; text['V'] = 145;text['W'] = 146;text['X'] = 147;text['Y'] = 148;
		text['Z'] = 149;
		text['!'] = 150; text['%'] = 151;text['('] = 152;text[')'] = 153;text['*'] = 154;
		text['+'] = 155; text[','] = 156;text['-'] = 157;text['.'] = 158;text['/'] = 159;
		text[':'] = 160; text[';'] = 161;text['<'] = 162;text['>'] = 163;text['?'] = 164;
		text['@'] = 165; text['['] = 166;text[']'] = 167;text['_'] = 168;text['{'] = 169;
		text['}'] = 170;
		text['0'] = 171; text['1'] = 172;text['2'] = 173;text['3'] = 174;text['4'] = 175;
		text['5'] = 176; text['6'] = 177;text['7'] = 178;text['8'] = 179;text['9'] = 180;
	}

	//�����̑Ή�����ԍ����擾
	int GetNumber(char t) { return text[t]; }
}