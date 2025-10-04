# Soyokaze — 初心者向け Runbook

このファイルはローカルの `doc`（およびリポジトリ上のマニュアル）を参照して作成した、初心者向けのユースケース別 Runbook です。

目的:
- Soyokaze の主要機能を短くまとめる
- 初めて使う人が「やりたいこと」をすばやく実行できる手順（Runbook）を提供する

※ 詳細なリファレンスは `doc/manuals/source` 以下や GitHub リポジトリの README を参照してください。

---

## 目次
- 概要と主要機能
- 事前準備（入手・起動）
- ユースケース別ハンドブック（初心者向け）
  - 1. アプリ起動とキー入力でコマンド実行（まずはここから）
  - 2. よく使うコマンドを登録する（永続化）
  - 3. ファイル／フォルダを送る（SendTo / Drag&Drop）
  - 4. ウィンドウ操作（Activate / Align）
  - 5. スニペット・クリップボード履歴の活用
  - 6. マクロとウォッチパス（自動処理）
  - 7. 検索（Everything 統合など）
- トラブルシューティング（よくある問題）
- 参考ドキュメント / 貢献ガイド

---

## 概要と主要機能
Soyokaze はコマンドランチャー型のユーティリティです。キーワード、スニペット、外部ツール、ウィンドウ操作、ファイル送信など幅広い操作を素早く行えるように設計されています。主な機能:

- インプットウィンドウ（ホットキーで呼び出す）からキーワードを入力してコマンドを実行
- ユーザーコマンド（ShellExecute、Web 検索、Snippet、Group、Directory Index、正規表現 マッチなど）
- アドホックコマンド（その場で実行できる一時コマンド）
- コマンドの登録（`new` / `registwin` / GUI による登録）
- ファイルやフォルダをドラッグ＆ドロップしてコマンドとして登録
- SendTo / 外部ツール連携
- ウィンドウの操作（アクティブ化、位置合わせ、整列など）
- スニペットとスニペットグループ、クリップボード履歴
- マクロ / WatchPath による自動処理
- 外部ライブラリ（Everything, tidy-html5, re2 等）との連携

---

## 事前準備（入手・起動）
- 公式リポジトリ: https://github.com/ampmmn/Soyokaze
- ローカルのドキュメント: `doc/manuals/source` 以下に詳細なマニュアルが入っています。
- 実行ファイル: `Soyokaze.exe` を起動するとアプリが立ち上がり、入力ウィンドウが有効になります。

起動手順（Windows）:
1. ビルド済の `Soyokaze.exe` を実行する（開発版なら Visual Studio から `src/Soyokaze.sln` をビルド）
2. 起動後、ホットキー（デフォルト: Alt+Space）で入力ウィンドウを開く
3. 入力ボックスにコマンド（キーワード）を入れて Enter で実行

---

## ユースケース別ハンドブック（簡潔手順）

### 1. アプリ起動とキー入力でコマンド実行（まずはここから）
シンプルな操作フロー:
1. アプリを起動
2. ホットキー（デフォルト: Alt+Space）を押して入力ウィンドウを表示
3. 入力欄に実行したいキーワードを入力（例: `notepad` や `browser`）
4. Enter を押してコマンドを実行

補足:
- 入力中に Tab で候補補完、矢印キー / マウスで候補選択ができます。
- F1 を押すと該当するマニュアル（ローカルの Help）が開きます。

参照: `doc/manuals/source/usage/how_to_use.md`

---

### 2. よく使うコマンドを登録する（永続化）
目的: 毎回入力する代わりに GUI でコマンドを登録しておく。

方法A: `new` コマンドから登録
1. 入力ウィンドウで `new` を入力して Enter
2. 表示されるコマンド種別から `ShellExecute` などを選択
3. コマンド編集画面で実行パス、引数、ラベルを入力して OK

方法B: `registwin`（現在アクティブなウィンドウを登録）
1. 登録したいウィンドウをアクティブにする
2. 入力ウィンドウで `registwin` を実行
3. 表示される登録画面で名前やコマンド情報を確定

補足:
- GUI の [Command Editor] で細かい実行設定（条件や引数、動作優先度）を設定できます。

参照: `doc/manuals/source/usage/how_to_use.md`、`doc/manuals/source/user-commands.md`

---

### 3. ファイル／フォルダを送る（SendTo / Drag&Drop）
用途: エクスプローラ上のファイルをアプリに登録して、特定の処理（例: 圧縮、アップロード）を簡単に実行する。

手順（Drag & Drop）:
1. 入力ウィンドウのアイコン領域をドラッグターゲットにする（入力ウィンドウが表示された状態）
2. エクスプローラからファイル/フォルダをドラッグして入力ウィンドウ上にドロップ
3. ドロップした対象を登録するためのコマンド編集画面が開くので、実行内容を設定して保存

SendTo を利用する場合:
- アプリ設定の「基本 > ショートカット登録」で `送る` を有効にすると、右クリックの SendTo メニューから登録できます。詳細は GUI の App Settings を確認してください。

参照: `doc/manuals/source/usage/how_to_use.md`

---

### 4. ウィンドウ操作（Activate / Align）
用途: ウィンドウをアクティブにしたり、複数ウィンドウを整列させるなどのデスクトップ操作。

例: ウィンドウをアクティブ化する
1. 入力ウィンドウで `activate-window` やそのショートカット名を使う（詳しいコマンド名は `user-command/activate-window.md` を参照）
2. 実行すると対象ウィンドウがアクティブ化される

例: ウィンドウの整列
- `align-window` コマンドで画面分割や整列を行えます。グループ化して効率的に並べる用途に便利です。

参照: `doc/manuals/source/user-command/activate-window.md`, `doc/manuals/source/user-command/align-window.md`

---

### 5. スニペット・クリップボード履歴の活用
用途: よく使うテキストをスニペットとして保持、またはクリップボードの履歴から貼り付け。

手順:
1. スニペットを作成: GUI の Snippet 管理画面で新規 Snippet を登録
2. 入力ウィンドウでスニペット名を入力して選択、Enter で貼り付けや実行
3. クリップボード履歴は設定から有効化しておく（Settings > Clipboard History）

参照: `doc/files/fragment/SnippetEdit.html`, `doc/files/fragment/ClipboardHistorySetting.html`

---

### 6. マクロとウォッチパス（自動処理）
用途: 特定フォルダの変更検知（WatchPath）で自動処理を起動したり、複数ステップの自動化をマクロで実行。

基本手順:
1. Settings の WatchPath に監視対象フォルダを登録
2. 変更イベントに対して実行させたいコマンドを設定
3. マクロ機能で複数コマンドをつなげることも可能

参照: `doc/manuals/source/macros.md`, `doc/manuals/source/user-command/watch-path.md`

---

### 7. 検索（Everything など）
用途: ファイル検索を高速に行い、コマンドに組み込む。

ポイント:
- externals に Everything 統合用の設定があり、アプリ内でファイル検索候補を表示できます。
- 検索はフィルタや正規表現と組み合わせて絞り込み可能

参照: `doc/files/fragment/EverythingSetting.html`, `doc/manuals/source/user-commands.md`

---

## トラブルシューティング（よくある問題）
- 入力ウィンドウが開かない: ホットキー設定を確認（Alt+Space デフォルト）。App Settings の Shortcut を確認してください。
- 登録や実行時に権限エラーが出る: 管理者権限を必要とするコマンドやファイル操作を実行している可能性があります。必要に応じてアプリを管理者権限で実行してください。
- ドラッグ＆ドロップが効かない: エクスプローラの権限レベルや UAC の影響でドラッグがブロックされることがあります。対象とアプリの権限を合わせてみてください。

---

## 参考ドキュメント / ファイル一覧（ローカル）
- マニュアルルート: `doc/manuals/source/index.md`
- はじめ方: `doc/manuals/source/usage/how_to_use.md`
- ユーザーコマンド群: `doc/manuals/source/user-commands.md`
- 各種コマンドの詳細は `doc/manuals/source/user-command/` と `doc/manuals/source/adhoc-command/` 以下を参照
- GUI のフラグメント（設定画面の HTML）: `doc/files/fragment` 以下

GitHub 上のオンラインマニュアル（プロジェクト本体）:
- https://github.com/ampmmn/Soyokaze

---

## 貢献・次のステップ
- 開発を進める場合は `develop` ブランチで作業し、実装が終わったら fork 側で Pull Request を作成してください（既にあなたの fork に develop を push済みです）。
- ドキュメントの追加要望があれば、この `doc/RUNBOOK.md` を編集して下さい。

---

作成者（自動生成補助）: local doc を参照して要約・手順化しました。より詳細なユースケース（特定のワークフロー）を追加したい場合は、例を教えてください。