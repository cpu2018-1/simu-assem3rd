形式について

./main BFILE [-s SFILE] [-i IFILE] [option]	([]は任意)
BFILE	:バイトコードのファイルの名前
SFILE	:デバッグ用の補助ファイルの名前
IFILE	:入力ファイルの名前
option	:-dのみ

統計の出力先はstatistics.txt(各命令の割合を%で表示)




デバッグモード(-d)のコマンドについて

<移動用>
n(next)			:次の命令に移ります(改行でも同じ)
l(line)    N		:アセンブリのN行目を実行したところまで移ります
lb(label)  LABEL	:アセンブリのLABELがさす命令を実行したところまで移ります
o(opecode) OPECODE	:OPECODE命令を実行したところまで移ります(OPECODEは小文字)
j(jump)    DEST		:上記3コマンドをまとめたものです(DESTは優先度の高い順にN > OPECODE > LABELとして判定)
c(count)   N		:N回目の命令が実行されるところまで移ります(nは0からスタート)
ll(last) 		:全命令が終了するところまで移ります
q(quit)			:プログラムを終了します

<表示用>
reg			:汎用レジスタの表を出力します
freg			:浮動小数点レジスタの表を出力します
mem N			:メモリ4*N番地の値をintで表示します
pc			:プログラムカウンタの値を表示します
io			:IOの値を表示します(OUTの出力先はstderr)

<その他>
左端に示されている数字はアセンブリの行番号です
jump命令や分岐命令で実際に分岐が行われる場合は分岐先を示す引数が光ります




