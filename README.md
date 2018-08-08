# PanicBNC - ZNC Fork

This is PanicBNC's fork of the [ZNC](https://github.com/znc/znc) IRC bouncer software. This version is modified to suit the needs of the PanicBNC software and may not suit the needs of others.

**This repository is NOT for submitting issues pertaining to the PanicBNC service. It is for the ZNC software in use by PanicBNC.**

## Changes
PanicBNC has made the following changes from upstream:

* Added the **Premium** flag.
* Disabled ident changes to users without the **Premium** flag.
* Disabled server changes & network additions to non-admins.
* Removal of log module.
* Added the **PanicBNC** module.
* Addition of third-party [**Palaver**](https://github.com/cocodelabs/znc-palaver) module.

*This is not intended to be an exhaustive list. The intention is to list **major** changes from upstream.*

## Contributions
PanicBNC gladly accepts Pull Requests and Issue submissions from the public. However, PanicBNC may determine the issue as **Upstream** and ask that the relevant submission be made to the [ZNC](https://github.com/znc/znc) repository. This ensures that the entire ZNC community as well as PanicBNC receive beneficial fixes.