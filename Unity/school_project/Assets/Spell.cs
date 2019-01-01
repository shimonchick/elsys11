using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Spell : MonoBehaviour {

    public abstract void Cast();
    [SerializeField]

    protected float cooldown = 2.0f;
}
