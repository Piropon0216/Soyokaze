# Backend Naming Convention Instructions

## Principles
可読性 / 予測可能性 / 衝突最小化。金融指標 + 変化率 + 集計期間を体系化。

## Metric Base Names
- price_close, price_open, volume, turnover, market_cap, eps, per, roe

## Derived Suffixes
| Suffix | Meaning | Example |
|--------|---------|---------|
| _change | 相対変化率 (current / prev - 1) | price_close_change |
| _diff | 絶対差 (current - prev) | volume_diff |
| _ma<n> | 移動平均 n | price_close_ma20 |
| _sma<n> | 単純移動平均 (同義) | price_close_sma5 |
| _pctile<p> | パーセンタイル | volume_pctile90 |
| _z | Zスコア | price_close_z |

## Time Window Prefix (Optional)
`w_` (週次集計), `m_` (月次), `q_` (四半期), `y_` (年次)
- 例: `w_price_close_change`

## Query Plan Tokens (DSL)
| Token | Purpose |
|-------|---------|
| SELECT <metric list> | 取得指標 |
| PERIOD <range expr> | 期間指定 (e.g., LAST 30D) |
| COMPARE <window> | 比較基準 (e.g., PREV_YEAR) |
| FILTER <predicate> | 条件 |
| ORDER BY <metric> [DESC] | ソート |

## File Naming
- agent: `<domain>_agent.py` (例: `market_data_agent.py`)
- adapter: `<system>_adapter.py` (`jquants_adapter.py`)
- test: `<module>_test.py`

## Avoid
- 重複意味 (price_close_close)
- 曖昧略語 (mc -> market_cap 明示)

## Collision Policy
既存 metrics と衝突する場合: DSL plan 生成で `ALIAS <new>` 指定し commit 前に metrics registry ドキュメント更新。

## References
- docs/nl_sql_value_change_semantics.md
- docs/nl_sql_diff_multi_sort_plan.md
