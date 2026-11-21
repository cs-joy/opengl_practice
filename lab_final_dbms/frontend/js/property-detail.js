/**
 * property-detail.js — Single property view + booking form (client portal).
 */

function getPropertyIdFromUrl() {
  const params = new URLSearchParams(window.location.search);
  return Number(params.get('id'));
}

function setText(id, text) {
  const el = document.getElementById(id);
  if (el) el.textContent = text ?? '';
}

async function loadPropertyDetail() {
  const propertyId = getPropertyIdFromUrl();
  const loading = document.getElementById('detail-loading');
  const content = document.getElementById('detail-content');
  const alertEl = document.getElementById('detail-alert');

  if (!propertyId) {
    if (loading) loading.hidden = true;
    showClientAlert(alertEl, 'Missing property id in URL.', 'error');
    return;
  }

  try {
    const property = await clientApi(`/public/properties/${propertyId}`);

    if (loading) loading.hidden = true;
    if (content) content.hidden = false;

    document.title = `${property.name} | KeyNest`;
    setText('detail-heading', property.name);
    setText('detail-address', property.address);
    setText('detail-rent', `${formatCurrency(property.rent_amount)} / month`);
    setText(
      'detail-description',
      property.description ||
        'No additional description provided for this listing.'
    );

    const statusEl = document.getElementById('detail-status');
    if (statusEl) {
      statusEl.textContent = property.status;
      statusEl.className = `badge ${statusBadgeClass(property.status)}`;
    }

    const detailVisual = document.querySelector('.detail-hero-visual');
    const detailImage = document.getElementById('detail-image');
    const imgSrc = propertyImageSrc(property.image);
    if (detailImage && imgSrc) {
      detailImage.src = imgSrc;
      detailImage.alt = property.name;
      detailImage.hidden = false;
      detailVisual?.classList.add('detail-hero-visual--has-image');
    } else if (detailImage) {
      detailImage.hidden = true;
      detailVisual?.classList.remove('detail-hero-visual--has-image');
    }

    const hiddenId = document.getElementById('booking-property-id');
    if (hiddenId) hiddenId.value = String(property.id);

    const panel = document.getElementById('booking-panel');
    const unavailableMsg = document.getElementById('booking-unavailable-msg');

    if (property.status !== 'available') {
      panel?.classList.add('booking-panel--disabled');
      if (unavailableMsg) unavailableMsg.hidden = false;
    }
  } catch (err) {
    if (loading) loading.hidden = true;
    showClientAlert(alertEl, err.message, 'error');
  }
}

async function handleBookingSubmit(event) {
  event.preventDefault();
  const form = document.getElementById('booking-form');
  const alertEl = document.getElementById('booking-alert');
  if (!form) return;

  const payload = Object.fromEntries(new FormData(form).entries());

  try {
    const booking = await clientApi('/public/bookings', {
      method: 'POST',
      body: JSON.stringify(payload),
    });
    showClientAlert(
      alertEl,
      `Thank you! Booking #${booking.id} is pending admin review.`,
      'success'
    );
    form.reset();
    const hiddenId = document.getElementById('booking-property-id');
    if (hiddenId) hiddenId.value = payload.property_id;
  } catch (err) {
    showClientAlert(alertEl, err.message, 'error');
  }
}

document.addEventListener('DOMContentLoaded', () => {
  loadPropertyDetail();
  const form = document.getElementById('booking-form');
  if (form) {
    form.addEventListener('submit', handleBookingSubmit);
  }
});
