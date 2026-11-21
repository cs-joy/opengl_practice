/**
 * client.js — Public listing: search form + property card grid.
 */

const gridEl = () => document.getElementById('property-grid');
const countEl = () => document.getElementById('results-count');
const searchForm = () => document.getElementById('search-form');
const listAlert = () => document.getElementById('client-list-alert');

/**
 * Build query string from search form values.
 * @param {HTMLFormElement} form
 */
function buildSearchQuery(form) {
  const data = new FormData(form);
  const params = new URLSearchParams();
  // Show every listing; booking stays limited to "available" on the detail page.
  params.set('bookable_only', '0');

  ['q', 'min_rent', 'max_rent'].forEach((key) => {
    const value = data.get(key);
    if (value !== null && String(value).trim() !== '') {
      params.set(key, String(value).trim());
    }
  });

  return params.toString();
}

function renderPropertyCards(properties) {
  const grid = gridEl();
  if (!grid) return;

  if (!properties.length) {
    grid.innerHTML = `
      <p class="empty-state" style="grid-column: 1 / -1">
        No properties match your search. Try different keywords or rent range.
      </p>`;
    return;
  }

  grid.innerHTML = properties
    .map((p) => {
      const excerpt =
        p.description && String(p.description).trim()
          ? escapeHtml(p.description)
          : 'View full details for this listing.';

      const imgSrc = propertyImageSrc(p.image);
      const visualClass = imgSrc
        ? 'property-card__visual property-card__visual--has-image'
        : 'property-card__visual';
      const imageTag = imgSrc
        ? `<img src="${imgSrc}" alt="" loading="lazy" />`
        : '';

      return `
      <article class="property-card">
        <div class="${visualClass}">
          ${imageTag}
          <span class="property-card__rent">${formatCurrency(p.rent_amount)}/mo</span>
        </div>
        <div class="property-card__body">
          <h3 class="property-card__title">${escapeHtml(p.name)}</h3>
          <p class="property-card__address">${escapeHtml(p.address)}</p>
          <p class="property-card__excerpt">${excerpt}</p>
          <div class="property-card__actions">
            <span class="badge ${statusBadgeClass(p.status)}">${escapeHtml(p.status)}</span>
            <a class="btn btn--primary btn--sm" href="/property.html?id=${p.id}">
              ${p.status === 'available' ? 'View &amp; book' : 'View details'}
            </a>
          </div>
        </div>
      </article>`;
    })
    .join('');
}

async function loadProperties(form) {
  const grid = gridEl();
  const count = countEl();

  if (grid) {
    grid.innerHTML =
      '<p class="loading" style="grid-column: 1 / -1">Searching…</p>';
  }

  try {
    const qs = buildSearchQuery(form || searchForm());
    const rows = await clientApi(`/public/properties?${qs}`);

    if (count) {
      count.textContent = `${rows.length} listing${rows.length === 1 ? '' : 's'}`;
    }
    renderPropertyCards(rows);
  } catch (err) {
    if (count) count.textContent = '—';
    if (grid) {
      grid.innerHTML = `<p class="empty-state" style="grid-column: 1 / -1">${escapeHtml(err.message)}</p>`;
    }
    showClientAlert(listAlert(), err.message, 'error');
  }
}

document.addEventListener('DOMContentLoaded', () => {
  const form = searchForm();
  if (!form) return;

  loadProperties(form);

  form.addEventListener('submit', (event) => {
    event.preventDefault();
    loadProperties(form);
  });
});
