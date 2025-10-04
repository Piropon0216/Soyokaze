# Backend Instructions

## Scope
Python Azure Functions + 分析ロジック (NL→Query プランニング, 特徴量計算) のガイド。金融データ特性 (遅延差異, 欠損, 市場休場) を考慮。

## CLEAR テンプレ適用
### 要求の核心
信頼できるドメイン変換 (RAW → canonical rows → features) をテスト駆動で一貫性確保。

### 実装手順
1. Red: 期待仕様(境界/休日/欠損) テスト追加
2. Green: パーサ/計算ロジック実装 (関数型, 副作用隔離)
3. Refactor: 重複除去 & I/O スキーマ固定
4. 観測: ログ/メトリクス埋め込み

### 技術仕様
- Python 3.11, type hints (mypy strict 相当想定)
- 構成: `src/agenticrag-functions/<agent>.py`
- ロジック分離: pure function (計算) + adapter (I/O)
- 例外: ドメイン例外クラスで分類 `DomainError | ExternalAPIError | ValidationError`
- 冪等性: 入力 (date, symbol, metric set) が同一ならハッシュ一致
- 制約: 1 function 実行 <= 5s / メモリ < 512MB 目標

### 期待する成果物
- [ ] 主要パーサ 100% ブランチカバレッジ
- [ ] 失敗ケース (欠損/市場休場) のシナリオテスト

## Coding Patterns
| Pattern | Use |
|---------|-----|
| functional core / imperative shell | 純粋ロジックテスト容易化 |
| dataclass Immutable | 計算結果構造保持 |
| result union (Success/Failure) | エラー集約と上位ハンドリング |

## Error Contract (例)
```python
@dataclass(frozen=True)
class Result(Generic[T]):
    ok: bool
    value: T | None = None
    error: str | None = None
```

## Logging Minimal Fields
`ts, level, agent, func, latency_ms, outcome, symbol(optional), planId`

## Testing Strategy
- Fast unit: 1秒以内 / I/O モック
- Contract: JSON Schema snapshot (計算結果)
- Property-based: 変化率計算 monotonic 条件

## Performance Guard
- 計算 O(n) 時系列長 n (n <= 5k) 以内
- キャッシュ層: 将来 Redis / 現状 in-process LRU 設計メモ

## References
- docs/plan_per_metric_change_pipeline_2025-09-16.md
- docs/backlog_jquants_nl_priorities.md
