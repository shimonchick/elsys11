using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PlayerController : Ship
{
    public float PlayerSpeed = 0.2f;

    [SerializeField]
    private float changeMaterialTime = 2.0f;
	//public string GameOverScene = "GameOver";
        
    [SerializeField]
    private List<Spell> spells;

    void Start()
    {
        if (AsteroidSpawner.Instance)
        {
            //AsteroidSpawner.Instance.RegisterPlayer(gameObject);
        }
		//GameStateController.Instance.RegisterPlayer (gameObject);
        foreach(Spell s in spells)
        {
            s.currentCooldown = 0;
        }
    }

    //void OnDestroy()
    //{
    //    AsteroidSpawner.Instance.UnregisterPlayer(gameObject);
	//	GameStateController.Instance.OnPlayerDied ();
    //}

    void FixedUpdate()
    {
        MoveShipWithPhysics();
    }

    void Update()
    {
        UpdateShootInputs();
        ReduceSpellCooldowns();
    }

    private void UpdateShootInputs()
    {
        if (Input.GetButton("Fire1"))
        {
            GetComponent<Weapon>().Shoot();
        }
    }

    private void ReduceSpellCooldowns()
    {
        foreach(Spell s in spells)
        {
            s.currentCooldown -= Time.deltaTime;
        }
    }

    private void MoveShipWithPhysics()
    {
        float verticalInput = Input.GetAxis("Vertical");
        float horizontalInput = Input.GetAxis("Horizontal");
        float playerCameraOffset = Camera.main.transform.position.y - transform.position.y;
        Vector3 mousePositionScreenSpace = new Vector3(Input.mousePosition.x, Input.mousePosition.y, playerCameraOffset);
        Vector3 mousePositionWorldSpace = Camera.main.ScreenToWorldPoint(mousePositionScreenSpace);

        Quaternion newRotation = Quaternion.LookRotation(mousePositionWorldSpace - transform.position);
        Vector3 direction = new Vector3(horizontalInput, 0, verticalInput);
        //direction = transform.rotation * direction;
        direction = direction * PlayerSpeed * Time.deltaTime;

        Rigidbody rb = GetComponent<Rigidbody>();
        rb.MovePosition(transform.position + direction);
        rb.MoveRotation(newRotation);
    }

    public void CastSpell(int index)
    {
        if (index > spells.Count)
        {
            return;
        }
        if (spells[index].currentCooldown <= 0)
        {
            spells[index].Cast();
            spells[index].currentCooldown = spells[index].Cooldown;
            Debug.Log("spell cast");
            StartCoroutine(UIManager.Instance.Cooldown(spells[index].Cooldown, index));
            Debug.Log("should have shown cooldown");
        }
       
    }

    public void ChangeMaterial(Material material)
    {
        Debug.Log("changing material");
        StartCoroutine(ChangeMaterial(material, changeMaterialTime));
    }

    public IEnumerator ChangeMaterial(Material material, float changeMaterialTime)
    {
        Debug.Log("changing material");

        Material oldMaterial = GetComponent<MeshRenderer>().material;
        GetComponent<MeshRenderer>().material = material;
        yield return  new WaitForSeconds(changeMaterialTime);
        GetComponent<MeshRenderer>().material = oldMaterial;
    }
}