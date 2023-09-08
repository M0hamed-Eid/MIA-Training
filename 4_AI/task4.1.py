class Weapon:
    def __init__(self, name, energy, damage, resources, description):
        self.name = name
        self.energy = energy
        self.damage = damage
        self.resources = resources
        self.description = description

    def use(self, opponent):
        pass

class Shield:
    def __init__(self, name, energy, save, resources, description):
        self.name = name
        self.energy = energy
        self.save = save
        self.resources = resources
        self.description = description

    def protect(self, damage):
        pass

class Villain:
    def __init__(self, name):
        self.name = name
        self.health = 100
        self.energy = 500
        self.shield = None
        self.weapon = None

    def set_weapon(self, weapon):
        self.weapon = weapon

    def set_shield(self, shield):
        self.shield = shield

    def attack(self, opponent):
        if self.weapon and self.energy >= self.weapon.energy:
            self.energy -= self.weapon.energy
            damage = self.weapon.damage
            opponent.defend(damage)
            return f"{self.name} used {self.weapon.name} and dealt {damage} damage."
        else:
            return f"{self.name} couldn't attack this round."

    def defend(self, damage):
        if self.shield:
            damage_reduction = self.shield.protect(damage)
            self.health -= damage_reduction
            return f"{self.name} used {self.shield.name} to block {damage_reduction} damage."
        else:
            self.health -= damage
            return f"{self.name} took {damage} damage with no shield."

class GruWeapon(Weapon):
    def use(self, opponent):
        if self.resources == "Inf":
            return super().use(opponent)
        else:
            if self.resources > 0:
                self.resources -= 1
                return super().use(opponent)
            else:
                return "Out of resources for this weapon."

class GruShield(Shield):
    def protect(self, damage):
        return self.save * damage / 100

class VectorWeapon(Weapon):
    def use(self, opponent):
        if self.resources == "Inf":
            return super().use(opponent)
        else:
            if self.resources > 0:
                self.resources -= 1
                return super().use(opponent)
            else:
                return "Out of resources for this weapon."

class VectorShield(Shield):
    def protect(self, damage):
        return self.save * damage / 100

def main():
    gru = Villain("Gru")
    vector = Villain("Vector")

    gru.set_weapon(GruWeapon("Freeze Gun", 50, 11, "Inf", "Immobilizes opponents temporarily."))
    gru.set_shield(GruShield("Energy-Projected BarrierGun", 20, 40, "Inf", "Absorbs energy-based attacks."))

    vector.set_weapon(VectorWeapon("Laser Blasters", 40, 8, "Inf", "Powerful laser blasters."))
    vector.set_shield(VectorShield("Energy Net Trap", 15, 32, "Inf", "Deploys an energy net."))

    round_count = 0

    while gru.health > 0 and vector.health > 0:
        round_count += 1
        print(f"Round {round_count}:")
        print(gru.attack(vector))
        print(vector.attack(gru))
        print(f"{gru.name} Health: {gru.health}, {vector.name} Health: {vector.health}")

        if gru.health <= 0:
            print(f"{gru.name} has been defeated. {vector.name} wins!")
            break
        elif vector.health <= 0:
            print(f"{vector.name} has been defeated. {gru.name} wins!")
            break

if __name__ == "__main__":
    main()





