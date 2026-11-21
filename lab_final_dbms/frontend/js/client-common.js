/**
 * client-common.js — Shared helpers for the public client portal.
 */

const CLIENT_API = '/api';

async function clientApi(endpoint, options = {}) {
  const response = await fetch(`${CLIENT_API}${endpoint}`, {
    headers: { 'Content-Type': 'application/json', ...(options.headers || {}) },
    ...options,
  });
  const data = await response.json().catch(() => ({}));
  if (!response.ok) {
    throw new Error(data.error || `Request failed (${response.status})`);
  }
  return data;
}

function escapeHtml(str) {
  const div = document.createElement('div');
  div.textContent = str ?? '';
  return div.innerHTML;
}

function formatCurrency(amount) {
  const num = Number(amount);
  if (Number.isNaN(num)) return '—';
  return new Intl.NumberFormat('en-BD', {
    style: 'currency',
    currency: 'BDT',
    maximumFractionDigits: 0,
  }).format(num);
}

function statusBadgeClass(status) {
  const map = {
    available: 'badge--available',
    occupied: 'badge--occupied',
    maintenance: 'badge--maintenance',
  };
  return map[status] || 'badge--unassigned';
}

/** Build URL for a filename stored in public/images/ */
function propertyImageSrc(image) {
  if (!image) return null;
  return `/images/${encodeURIComponent(image)}`;
}

function showClientAlert(el, message, type = 'success') {
  if (!el) return;
  el.textContent = message;
  el.className = `alert alert--${type} alert--visible`;
  window.setTimeout(() => el.classList.remove('alert--visible'), 5000);
}