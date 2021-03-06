c++言語によるUECdaクライアントです。
* 作成にあたりUECda公式サイトで公開されている標準クライアントと2005年優勝クライアントのsnowlを参考にしています。通信部分はほとんど拝借しています。
* Makefileは（http://urin.github.io/posts/2013/simple-makefile-for-clang/）を拝借しております。
* 現在標準クライアント的な提出方式と単純なモンテカルロ手法による提出方式の2つを実装しています。
* コメントを過多に書くよう心がけています。
* 拙いプログラムであり、また思い付きにより再構築を繰り返しているため、今後構造を含めてがらりと変わる可能性があります。
* 高速化とかを考えていないので、特にモンテカルロは時間制限に引っかかると思います。

###main関数
main.cppに書いてあります。
通信部分・ゲームの管理はGameクラスが担当しています。
各種通信はUECdaプロトコルと対応しているため、「game.～」を削除したり順序を入れ替えたりすると動かなくなります。
Gameクラスが思考部分とサーバの仲介役のような立場であると考えます。
現在提出手の思考はselectLikeDefault()によります。
選んだカードはselect_cardsに保存されます。[8][15]配列に整形して、gameに提示することで提出をします。

###カードの表現
Card.hに定義が書いてあります。1つの役はclassにより定義されています。余分な変数が多いです。
提出役の特性（ランク、階段、など）は関数に問い合わせることで確認ができます。

###盤面の表現
Table.hに定義が書いてあります。こちらもclassにより定義されています。
場の特性（ランク、革命、など）は関数に問い合わせることで確認ができます。

###手の提出
現在の盤面での合法手展開を行い（makeAllYaku）、その中から提出する役を選ぶ、という形式をとっています。
selectLikeDefault()は、標準クライアントのような提出方法です。
* 場が空のときは階段、ペア、単騎の順に探していく
 * 見つかったら枚数の多いものを出す
* 場が何かある場合は以下の点に注意して提出
 * なるべくjokerを使わない（出せなければやむなし）
 * 場札の枚数以上の役を作れるなら使わない（ただし縛りのときは見逃す）
* jokerの使い方あたりで若干の違いがあるので、厳密に同じ手を提出するわけではない（直すか検討）
* その他異なる点等あるやもしれません。

selectByDelusion()は、モンテカルロ法（もどき）を使う提出方法です。
* シミュレーションと呼ぶにはおこがましい代物なのでソース内ではDelusionと表現している。（モンテカルロ法というと実際に試合をやっているかのようだが、実際には仮想敵を用意して試合を妄想する）
* 各合法手はすべて列挙したうえで、各手に対して200回の回数シミュレーションを行っている。
* 仮想敵は標準クライアントの提出方法。
* snowlなど強いプログラムは仮想敵の提出方法に機械学習を用いている。
* また厳密に全合法手を考えているわけではない。

###実行方法
UECda公式サイトの標準クライアントの実行方法と同じです。
http://uecda.nishino-lab.jp/document/development/
Cygwin上での実行は確認しています。公式にはconfigureコマンドがありますが、こちらは不要です。
現状、warningが沢山出ると思います（直す予定）。
