#include "TextManager.h"
#include <map>

/// <summary>
/// 日本語のテキスト管理
/// </summary>
namespace TextManager
{
	//日本語表示するための連想配列
	std::map<char, int> text;

	//初期化
	void TextManager::Initialize()
	{
		text['あ'] = 0;  text['い'] = 1; text['う'] = 2; text['え'] = 3; text['お'] = 4;
		text['か'] = 5;  text['き'] = 6; text['く'] = 7; text['け'] = 8; text['こ'] = 9;
		text['さ'] = 10; text['し'] = 11;text['す'] = 12;text['せ'] = 13;text['そ'] = 14;
		text['た'] = 15; text['ち'] = 16;text['つ'] = 17;text['て'] = 18;text['と'] = 19;
		text['な'] = 20; text['に'] = 21;text['ぬ'] = 22;text['ね'] = 23;text['の'] = 24;
		text['は'] = 25; text['ひ'] = 26;text['ふ'] = 27;text['へ'] = 28;text['ほ'] = 29;
		text['ま'] = 30; text['み'] = 31;text['む'] = 32;text['め'] = 33;text['も'] = 34;
		text['や'] = 35; text['ゆ'] = 36;text['よ'] = 37;
		text['ら'] = 38; text['り'] = 39;text['る'] = 40;text['れ'] = 41;text['ろ'] = 42;
		text['わ'] = 43; text['を'] = 44;text['ん'] = 45;
		text['ゃ'] = 46; text['ゅ'] = 47;text['ょ'] = 48;
		text['ア'] = 49; text['イ'] = 50;text['ウ'] = 51;text['エ'] = 52;text['オ'] = 53;
		text['カ'] = 54; text['キ'] = 55;text['ク'] = 56;text['ケ'] = 57;text['コ'] = 58;
		text['サ'] = 59; text['シ'] = 60;text['ス'] = 61;text['セ'] = 62;text['ソ'] = 63;
		text['タ'] = 64; text['チ'] = 65;text['ツ'] = 66;text['テ'] = 67;text['ト'] = 68;
		text['ナ'] = 69; text['ニ'] = 70;text['ヌ'] = 71;text['ネ'] = 72;text['ノ'] = 73;
		text['ハ'] = 74; text['ヒ'] = 75;text['フ'] = 76;text['ヘ'] = 77;text['ホ'] = 78;
		text['マ'] = 79; text['ミ'] = 80;text['ム'] = 81;text['メ'] = 82;text['モ'] = 83;
		text['ヤ'] = 84; text['ユ'] = 85;text['ヨ'] = 86;
		text['ラ'] = 87; text['リ'] = 88;text['ル'] = 89;text['レ'] = 90;text['ロ'] = 91;
		text['ワ'] = 92; text['ヲ'] = 93;text['ン'] = 94;
		text['ャ'] = 95; text['ュ'] = 96;text['ョ'] = 97;
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