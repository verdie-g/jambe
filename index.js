const jambeAddon = require('./build/Release/jambeaddon.node');

const router = new jambeAddon.Router();
router.addRoute('/abc', 1, () => { console.log('mdr'); });

module.exports = jambeAddon;
