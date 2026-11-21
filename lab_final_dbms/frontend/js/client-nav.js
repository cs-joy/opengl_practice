/**
 * client-nav.js — Active menubar link + responsive hamburger menu.
 */
document.addEventListener('DOMContentLoaded', () => {
  const page = document.body.dataset.page;

  document.querySelectorAll('.client-nav a[data-nav]').forEach((link) => {
    if (link.dataset.nav === page) {
      link.classList.add('is-active');
    }
  });

  const menuBtn = document.getElementById('client-menu-btn');
  const nav = document.getElementById('client-nav');
  const overlay = document.getElementById('client-nav-overlay');

  if (!menuBtn || !nav) return;

  function setMenuOpen(open) {
    menuBtn.setAttribute('aria-expanded', open ? 'true' : 'false');
    menuBtn.setAttribute('aria-label', open ? 'Close menu' : 'Open menu');
    nav.classList.toggle('client-nav--open', open);
    if (overlay) {
      overlay.classList.toggle('client-nav-overlay--visible', open);
      overlay.setAttribute('aria-hidden', open ? 'false' : 'true');
    }
    document.body.classList.toggle('client-menu-open', open);
  }

  function toggleMenu() {
    const isOpen = menuBtn.getAttribute('aria-expanded') === 'true';
    setMenuOpen(!isOpen);
  }

  menuBtn.addEventListener('click', toggleMenu);

  if (overlay) {
    overlay.addEventListener('click', () => setMenuOpen(false));
  }

  nav.querySelectorAll('a').forEach((link) => {
    link.addEventListener('click', () => setMenuOpen(false));
  });

  document.addEventListener('keydown', (event) => {
    if (event.key === 'Escape') {
      setMenuOpen(false);
    }
  });

  window.addEventListener('resize', () => {
    if (window.innerWidth > 768) {
      setMenuOpen(false);
    }
  });
});
