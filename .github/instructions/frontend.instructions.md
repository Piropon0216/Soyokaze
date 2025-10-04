# Frontend Instructions

## Scope
React + TypeScript での金融分析 UI: NL クエリ入力 → プラン結果可視化 (チャート / テーブル / 重要指標バッジ)。

## CLEAR
### 要求の核心
ユーザが自然言語で入力した分析要求を 3ステップ以内で視覚化する高速な対話体験。

### 実装手順
1. QueryForm (入力バリデーション + 例示) 実装
2. useAgenticRAG フック: 呼出/ステート/リトライ
3. ResultViews: 時系列 / 分布 / メタ情報
4. エラーバナー + Telemetry 埋め込み

### 技術仕様
- React 18+, Vite or CRA → (将来 Vite 移行) 想定
- 状態: 軽量 (useState) + 将来複雑化すれば Zustand
- チャート: 初期 Recharts / D3 導入前抽象
- 型: strict true, no implicit any
- アクセシビリティ: フォーカスリング + aria-label 必須

### 期待する成果物
- [ ] NL→結果 レイテンシ 1秒以内 (ローカル計測)
- [ ] コンポーネント単体テスト > 80% 行カバレッジ

## コンポーネント階層 (MVP)
```
components/
  QueryForm.tsx
  ResultTabs.tsx
  charts/TimeSeriesChart.tsx
  charts/DistributionChart.tsx
  meta/PlanSummary.tsx
hooks/
  useAgenticRAG.ts
services/
  apiClient.ts
```

## UI/UX 指針
- Skeletal Loading: チャート領域プレースホルダ
- エラー: 上部固定 dismissible アラート
- ダークモード: CSS 変数でトークン化

## テスト
- react-testing-library + vitest / jest
- QueryForm: 入力validation→API呼び出し発火
- useAgenticRAG: 成功/失敗/キャンセル

## パフォーマンス
- Lazy import heavy charts
- メモ化: 計算コスト高い集計のみ useMemo

## セキュリティ
- XSS: JSX 自由テキスト sanitize (DOMPurify)
- API: 信頼できない文字列 encodeURIComponent

## References
- docs/VISUALIZATION_BACKLOG.md
- docs/VISUALIZATION_MCP_SLICE.md
