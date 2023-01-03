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
		text['f'] = 103; text['g'] = 104;text['h'] = 105;text['n'] = 106;text['o'] = 107;
		text['p'] = 108; text['q'] = 109;text['r'] = 110;text['s'] = 111;text['t'] = 112;
		text['u'] = 113; text['v'] = 114;text['w'] = 115;text['x'] = 116;text['y'] = 117;
		text['z'] = 118;
		text['A'] = 119; text['B'] = 120;text['C'] = 121;text['D'] = 122;text['E'] = 123;
		text['F'] = 124; text['G'] = 125;text['H'] = 126;text['I'] = 127;text['J'] = 128;
		text['K'] = 129; text['L'] = 130;text['M'] = 131;text['N'] = 132;text['O'] = 133;
		text['P'] = 134; text['Q'] = 135;text['R'] = 136;text['S'] = 137;text['T'] = 138;
		text['U'] = 139; text['V'] = 140;text['W'] = 141;text['X'] = 142;text['Y'] = 143;
		text['Z'] = 144;
		text['!'] = 145; text['%'] = 146;text['('] = 147;text[')'] = 148;text['*'] = 149;
		text['+'] = 150; text[','] = 151;text['-'] = 152;text['.'] = 153;text['/'] = 154;
		text[':'] = 155; text[';'] = 156;text['<'] = 157;text['>'] = 158;text['?'] = 159;
		text['@'] = 160; text['['] = 161;text[']'] = 162;text['_'] = 163;text['{'] = 164;
		text['}'] = 165;
		text['0'] = 166; text['1'] = 167;text['2'] = 168;text['3'] = 169;text['4'] = 170;
		text['5'] = 171; text['6'] = 172;text['7'] = 173;text['8'] = 174;text['9'] = 175;
	}

	//�����̑Ή�����ԍ����擾
	int GetNumber(char t) { return text[t]; }
}