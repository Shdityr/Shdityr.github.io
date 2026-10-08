'use strict';

/*
 * markdown-it 插件：保护数学公式，不渲染。
 *
 * 作用是把 $...$ 和 $$...$$ 整体切成一个 token，原样输出给前端 MathJax。
 * 这样公式内部的 * _ 等字符就不会被 Markdown 当成斜体/强调解析掉。
 *
 * 背景：旧站用 marked 渲染，$numb*X-B=numw*X-W$ 里的 *X-B=numw* 被当成了
 * 斜体，生成 <em>，公式直接坏掉。换成这个插件后不会再发生。
 *
 * 分词逻辑参考 markdown-it-katex。
 */

function isValidDelim(state, pos) {
  const max = state.posMax;
  const prev = pos > 0 ? state.src.charCodeAt(pos - 1) : -1;
  const next = pos + 1 <= max ? state.src.charCodeAt(pos + 1) : -1;
  return {
    // 开定界符后面不能紧跟空白
    canOpen: !(next === 0x20 || next === 0x09),
    // 闭定界符前面不能是空白，后面不能是数字（避免把 "$5 和 $6" 误判成公式）
    canClose: !(prev === 0x20 || prev === 0x09 || (next >= 0x30 && next <= 0x39))
  };
}

function mathInline(state, silent) {
  if (state.src[state.pos] !== '$') return false;

  if (!isValidDelim(state, state.pos).canOpen) {
    if (!silent) state.pending += '$';
    state.pos += 1;
    return true;
  }

  const start = state.pos + 1;
  let match = start;
  let pos;
  while ((match = state.src.indexOf('$', match)) !== -1) {
    // 跳过被反斜杠转义的 \$
    pos = match - 1;
    while (state.src[pos] === '\\') pos -= 1;
    if ((match - pos) % 2 === 1) break;
    match += 1;
  }

  if (match === -1) {                      // 没有闭合
    if (!silent) state.pending += '$';
    state.pos = start;
    return true;
  }
  if (match - start === 0) {               // 空的 $$
    if (!silent) state.pending += '$$';
    state.pos = start + 1;
    return true;
  }
  if (!isValidDelim(state, match).canClose) {
    if (!silent) state.pending += '$';
    state.pos = start;
    return true;
  }

  if (!silent) {
    const token = state.push('math_inline', 'math', 0);
    token.markup = '$';
    token.content = state.src.slice(start, match);
  }
  state.pos = match + 1;
  return true;
}

function mathBlock(state, startLine, endLine, silent) {
  let pos = state.bMarks[startLine] + state.tShift[startLine];
  let max = state.eMarks[startLine];

  if (pos + 2 > max) return false;
  if (state.src.slice(pos, pos + 2) !== '$$') return false;
  pos += 2;

  let firstLine = state.src.slice(pos, max);
  if (silent) return true;

  let found = false;
  if (firstLine.trim().slice(-2) === '$$') {
    firstLine = firstLine.trim().slice(0, -2);
    found = true;
  }

  const lines = found ? [] : [firstLine];
  let next = startLine;
  while (!found) {
    next += 1;
    if (next >= endLine) break;
    pos = state.bMarks[next] + state.tShift[next];
    max = state.eMarks[next];
    if (pos < max && state.tShift[next] < state.blkIndent) break;

    let line = state.src.slice(pos, max);
    if (line.trim().slice(-2) === '$$') {
      line = line.trim().slice(0, -2);
      found = true;
    }
    lines.push(line);
  }

  state.line = next + 1;
  const token = state.push('math_block', 'math', 0);
  token.block = true;
  token.content = (firstLine && !lines.length ? firstLine : lines.join('\n')).trim();
  token.markup = '$$';
  token.map = [startLine, state.line];
  return true;
}

module.exports = function mathProtect(md) {
  const esc = md.utils.escapeHtml;
  md.inline.ruler.after('escape', 'math_inline', mathInline);
  md.block.ruler.after('blockquote', 'math_block', mathBlock, {
    alt: ['paragraph', 'reference', 'blockquote', 'list']
  });
  // 原样吐回去，由前端 MathJax 负责渲染
  md.renderer.rules.math_inline = (tokens, idx) => '$' + esc(tokens[idx].content) + '$';
  md.renderer.rules.math_block = (tokens, idx) => '$$' + esc(tokens[idx].content) + '$$\n';
};
