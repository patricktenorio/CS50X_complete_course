// My Header HTML template
class myHeader extends HTMLElement {
    connectedCallback() {
        this.innerHTML = `
        <!-- Header Section -->
        <div class="header">
            <!-- BS Navbar -->
            <nav class="navbar navbar-expand-lg navbar-dark bg-dark">
                <div class="container">
                    <!-- My Logo -->
                    <a class="navbar-brand" href="index.html">
                        <img src="img/PT Logo.png" alt="logo" width="40">
                    </a>
                    <!-- Navbar Collapse Menu -->
                    <button class="navbar-toggler" type="button" data-bs-toggle="collapse"
                        data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent"
                        aria-expanded="false" aria-label="Toggle navigation">
                        <span class="navbar-toggler-icon"></span>
                    </button>
                    <!-- Navbar Links -->
                    <div class="collapse navbar-collapse" id="navbarSupportedContent">
                        <ul class="navbar-nav ms-auto mt-2 mt-lg-0">
                            <li class="nav-item">
                                <a class="nav-link" href="index.html">PyHOME</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link" href="journey.html">PyJOURNEY</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link" href="projects.html">PyPROJECTS</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link" href="certificates.html">PyCERTS</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link" href="contact.html">CONTACT.me</a>
                            </li>
                        </ul>
                    </div>
                </div>
            </nav>
        </div>
        `
    }
}
customElements.define('my-header', myHeader)

// My Footer HTML template
class myFooter extends HTMLElement {
    connectedCallback() {
        this.innerHTML = `
        <!-- Footer Section -->
        <div class="footer">
            <div class="container">
                <div class="social-media text-center">
                    <ul class="footer-list">
                        <li><a href="https://linkedin.com/in/patrick-tenorio-b980a1187/" target="_blank"><i class='bx bxl-linkedin-square'></i></a></li>
                        <li><a href="https://github.com/patricktenorio" target="_blank"><i class='bx bxl-github'></i></a></li>
                        <li><a href="https://twitter.com/devtrick_" target="_blank"><i class='bx bxl-twitter'></i></a></li>
                        <li><a href="https://facebook.com/patrick.tenorio.3" target="_blank"><i class='bx bxl-facebook-square'></i></a></li>
                    </ul>
                    <p>Patrick Tenorio © 2022 - All rigths reserved.</p>
                </div>
            </div>
        </div>
        `
    }
}
customElements.define('my-footer', myFooter)

// Auto Typing Script
var typed = new Typed(".auto-type", {
    strings: ["learning Python Programming"],
    typeSpeed: 50,
    backSpeed: 50,
    loop: true
})