void GameObject::Dragon::doCollide(Hero* h) {
    y -= lastDir.first;
    x -= lastDir.second;
}
void GameObject::Dragon::doCollide(Zombie* z) {
    y -= lastDir.first;
    x -= lastDir.second;
}
void GameObject::Dragon::doCollide(Princess* p) {
    damage(p->getDamagePower());
}
void GameObject::Dragon::doCollide(Projectile* p) {
    damage(p->getDamagePower());
}
void GameObject::Dragon::doCollide(Dragon* d) {
    y -= lastDir.first;
    x -= lastDir.second;
}
void GameObject::Dragon::doCollide(Trap* t) {
    damage(t->getDamagePower());
}
void GameObject::Dragon::doCollide(Wall* w) {
    y -= lastDir.first;
    x -= lastDir.second;
}
void GameObject::Dragon::doCollide(Medkit* m) {}