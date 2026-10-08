# Shdityr 的博客 — 源文件

线上地址：https://shdityr.github.io

## 这个仓库怎么组织的

同一个仓库，两个分支，各管各的：

| 分支 | 放什么 | 谁来改 |
|------|--------|--------|
| `source` | Hexo 源文件（Markdown 文章、配置） | **你**，平时只动这个分支 |
| `master` | 生成出来的 HTML | GitHub Actions 自动写，别手动改 |

流程：你推 Markdown 到 `source` → GitHub Actions 自动跑 `hexo generate` → 把结果推到 `master` → GitHub Pages 发布。

所以**本地不装任何东西也能发文章**，在 GitHub 网页上直接编辑 Markdown 就行。

## 写一篇新文章

```bash
npx hexo new post 文章名
```

会生成 `source/_posts/文章名.md` 和一个同名文件夹。文章里的图片、代码放进那个文件夹，用相对路径引用：

```markdown
![配图](0.jpg)
[code](1.cpp)
```

然后推上去就完事了：

```bash
git add -A && git commit -m "新文章：XXX" && git push
```

## 本地预览

```bash
npm install          # 只有第一次需要
npx hexo server      # 打开 http://localhost:4000
```

改完文件会自动刷新，不用重启。

## 几个需要知道的点

**公式**：用 `$...$` 写行内公式，`$$...$$` 写行间公式，由浏览器端的 MathJax 渲染。

`lib/markdown-it-math-protect.js` 这个小插件会把公式整块保护起来再交给 Markdown 解析。**别删它**——旧站就是因为没有这层保护，`$numb*X-B=numw*X-W$` 里的 `*...*` 被 Markdown 当成了斜体，公式直接渲染坏掉。

之所以不在构建时把公式渲染成 SVG，是因为 `wll` 那篇有 444 个公式，预渲染会让页面从 38KB 涨到 2.3MB。

**配置文件**：
- `_config.yml` — 站点配置（标题、链接格式、Markdown 渲染器）
- `_config.next.yml` — NexT 主题配置（配色、菜单、侧边栏）

主题是 npm 包 `hexo-theme-next`，不要去改 `node_modules` 里的文件，所有定制都写在 `_config.next.yml` 里。

## 这个博客的来历

2019 年 8 月用 Hexo 3.9 + NexT 7.3 搭的，当时只把生成的 HTML 推到了 GitHub，源文件在旧电脑上丢了。

2026 年 10 月从线上 HTML 反推出 Markdown 恢复，并升级到 Hexo 8 + NexT 8。三篇文章的正文经逐字节比对，与原站完全一致。

顺带修了两个旧问题：

1. `_config.yml` 里的 `url` 一直是默认的 `http://yoursite.com`，导致页面里的绝对链接全是错的，已改成真实域名
2. 前面说的公式被 Markdown 啃坏的 bug，共 3 处

> 如果哪天翻出了旧电脑上的原始源文件，可以拿 `source/_posts/*.md` 对一下。
> 反推出来的版本正文可靠，但 front-matter 里只有标题、日期和标签——
> 当年如果还写过别的字段（比如分类、封面图），那是反推不出来的。
