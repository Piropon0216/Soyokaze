# Testing Instructions

## Philosophy
"仕様の最初の表現はテスト" (CHANGELOG FIRST と両輪)。金融ドメイン固有の境界 (市場休場, 欠損, 低流動) を最初に Red 化。

## Pyramid (割合目安)
- Unit 65%
- Property / Contract 20%
- Integration (Functions 呼出) 10%
- E2E (UI) 5%

## CLEAR
### 要求の核心
高頻度リファクタでも意思決定速度を落とさない回帰安全網。

### 実装手順
1. 重要経路識別 (NL→Plan, Plan→Features, Features→Chart)
2. 失敗パターン列挙 (欠損/無効期間/未知メトリク)
3. テストスケルトン生成
4. 実装 & カバレッジ計測 → ギャップ埋め

### 技術仕様
- Coverage: lines >= 85%, critical modules >= 100%
- Mutation (将来導入検討) surviving mutants < 10%
- Snapshot: JSON schema versioned (破壊的変更検知)

### 期待する成果物
- [ ] coverage report artifact
- [ ] schema diff PR コメント
- [ ] markdown link check パス (`npm run check:links`)

## Naming
`<module>.test.ts` / `<agent>_feature.test.py`

## Lint + Type + Test Gate (CI)
1. ts typecheck
2. python mypy (strict subset)
3. unit tests parallel
4. coverage upload & threshold check

## Flake Handling
- 3回再試行で再発 → lessons へエントリ + Changelog

## References
- docs/agent_handoff_lessons.md
