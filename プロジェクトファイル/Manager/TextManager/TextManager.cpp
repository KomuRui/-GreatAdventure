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
		text['a']  = 96; text['b']  = 97;text['c']  = 98;text['d']  = 99;text['e'] = 100;
		text['f'] = 101; text['g'] = 102;text['h'] = 103;text['i'] = 104;text['j'] = 105;
		text['k'] = 106; text['l'] = 107;text['m'] = 108;text['n'] = 109;text['o'] = 110;
		text['p'] = 111; text['q'] = 112;text['r'] = 113;text['s'] = 114;text['t'] = 115;
		text['u'] = 116; text['v'] = 117;text['w'] = 118;text['x'] = 119;text['y'] = 120;
		text['z'] = 121;
		text['A'] = 122; text['B'] = 123;text['C'] = 124;text['D'] = 125;text['E'] = 126;
		text['F'] = 127; text['G'] = 128;text['H'] = 129;text['I'] = 130;text['J'] = 131;
		text['K'] = 132; text['L'] = 133;text['M'] = 134;text['N'] = 135;text['O'] = 136;
		text['P'] = 137; text['Q'] = 138;text['R'] = 139;text['S'] = 140;text['T'] = 141;
		text['U'] = 142; text['V'] = 143;text['W'] = 144;text['X'] = 145;text['Y'] = 146;
		text['Z'] = 147;
		text['!'] = 148; text['%'] = 149;text['('] = 150;text[')'] = 151;text['*'] = 152;
		text['+'] = 153; text[','] = 154;text['-'] = 155;text['.'] = 156;text['/'] = 157;
		text[':'] = 158; text[';'] = 159;text['<'] = 160;text['>'] = 161;text['?'] = 162;
		text['@'] = 163; text['['] = 164;text[']'] = 165;text['_'] = 166;text['{'] = 167;
		text['}'] = 168;
		text['0'] = 169; text['1'] = 170;text['2'] = 171;text['3'] = 172;text['4'] = 173;
		text['5'] = 174; text['6'] = 175;text['7'] = 176;text['8'] = 177;text['9'] = 178;
	}
}