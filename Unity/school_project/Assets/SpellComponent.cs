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
        if (spells[index].currentCooldown <= 0)
        {
            spells[index].currentCooldown = spells[index].Cooldown;
            Spell spell = Instantiate(spells[index]);
            spell.Caster = gameObject;
            spell.Cast();
            Destroy(spell);
            Debug.Log("should show cooldown with index:" + index + "and time:" + spell.Cooldown);
            StartCoroutine(UIManager.Instance.Cooldown(spell.Cooldown, index));
            //spells[index].currentCooldown = spells[index].Cooldown;
        }
    }

    private void Start()
    {
        foreach(Spell s in spells)
        {
            s.currentCooldown = 0.0f;
        }
    }
    private void Update()
    {
        foreach(Spell s in spells)
        {
            if (s.currentCooldown > 0)
            {
                s.currentCooldown -= Time.deltaTime;
            }
        }
    }
}
