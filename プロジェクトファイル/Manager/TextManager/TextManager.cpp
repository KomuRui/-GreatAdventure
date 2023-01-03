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

	//文字の対応する番号を取得
	int GetNumber(char t) { return text[t]; }
}