using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpellComponent : MonoBehaviour {

    [SerializeField]
    private List<Spell> spells;

    public void CastSpell(int index)
    {
        if(index >= spells.Count || index < 0)
        {
            return;
        }
        Spell spell = Instantiate(spells[index]);
        spell.Caster = gameObject;
        spell.Cast();
        Destroy(spell);
    }
}
