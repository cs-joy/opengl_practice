/**
 * home.js — Landing page: hero carousel + featured property cards.
 */

/** One visible slide + opacity transition (lighter than 3× infinite CSS anims). */
function initHeroCarousel() {
  if (window.matchMedia('(prefers-reduced-motion: reduce)').matches) {
    return;
  }

  const slides = document.querySelectorAll('.hero-carousel__slide');
  const dots = document.querySelectorAll('.hero-carousel__dot');
  if (slides.length < 2) return;

  let index = 0;
  let timerId = null;
  const INTERVAL_MS = 5500;

  function showSlide(nextIndex) {
    slides[index].classList.remove('is-active');
    dots[index]?.classList.remove('is-active');
    index = nextIndex;
    slides[index].classList.add('is-active');
    dots[index]?.classList.add('is-active');
  }

  function start() {
    stop();
    timerId = window.setInterval(() => {
      showSlide((index + 1) % slides.length);
    }, INTERVAL_MS);
  }

  function stop() {
    if (timerId !== null) {
      window.clearInterval(timerId);
      timerId = null;
    }
  }

  start();

  document.addEventListener('visibilitychange', () => {
    if (document.hidden) {
      stop();
    } else {
      start();
    }
  });
}

function renderFeaturedCard(p) {
  const imgSrc = propertyImageSrc(p.image);
  const visualClass = imgSrc
    ? 'property-card__visual property-card__visual--has-image'
    : 'property-card__visual';
  const imageTag = imgSrc
    ? `<img src="${imgSrc}" alt="" loading="lazy" />`
    : '';
  const excerpt =
    p.description && String(p.description).trim()
      ? escapeHtml(p.description)
      : 'View listing details.';

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
            View details
          </a>
        </div>
      </div>
    </article>`;
}

document.addEventListener('DOMContentLoaded', async () => {
  initHeroCarousel();

  const grid = document.getElementById('home-featured-grid');
  const countEl = document.getElementById('home-listing-count');

  if (!grid) return;

  try {
    const rows = await clientApi('/public/properties?bookable_only=0');
    if (countEl) {
      countEl.textContent = String(rows.length);
    }

    const featured = rows.slice(0, 3);
    if (!featured.length) {
      grid.innerHTML =
        '<p class="empty-state" style="grid-column:1/-1">No listings yet.</p>';
      return;
    }

    grid.innerHTML = featured.map(renderFeaturedCard).join('');
  } catch (err) {
    grid.innerHTML = `<p class="empty-state" style="grid-column:1/-1">${escapeHtml(err.message)}</p>`;
  }
});
