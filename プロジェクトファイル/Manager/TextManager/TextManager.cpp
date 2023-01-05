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

	//文字の対応する番号を取得
	int GetNumber(char t) { return text[t]; }
}