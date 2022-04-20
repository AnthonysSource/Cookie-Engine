#pragma once

#include "Core/Defines.h"
#include "Core/Types/Containers.h"
#include "Core/Types/PrimitiveTypes.h"
#include "Core/Math.h"
#include "Core/Random/Random.h"

#include "Entities/Common.h"
#include "Entities/ComponentArray.h"
#include "Entities/System.h"
#include "Entities/BaseComponents.h"

namespace Cookie {

	// -----------------------------------------------------------------

	class EntityAdmin {

	public:
		void Init();
		void Update();
		void Shutdown();

		// Entities
		// -----------------------------------------------------------------

		EntityID CreateEntity();
		void DestroyEntity(EntityID entity);

		// Components
		// -----------------------------------------------------------------

		template <typename T> void RegisterComponent() {
			u32 typeID = typeid(T).hash_code();
			ComponentArray<T> *array = new ComponentArray<T>();
			m_ComponentArrays.insert({typeID, array});
			m_ComponentSignatureIndex.insert({typeID, m_NextComponentIndex});
			++m_NextComponentIndex;
		};

		template <typename T> void AddComponent(EntityID entity, T component) {
			GetComponentArray<T>()->Insert(entity, component);

			auto signature = m_Signatures[entity];
			signature.set(GetComponentSignatureID<T>(), true);
			m_Signatures[entity] = signature;

			EntitySignatureChanged(entity);
		};

		template <typename T> void RemoveComponent(EntityID entity) {
			GetComponentArray<T>()->Remove(entity);

			auto signature = m_Signatures[entity];
			signature.set(GetComponentSignatureID<T>(), false);
			m_Signatures[entity] = signature;

			EntitySignatureChanged(entity);
		};

		template <typename T> T *GetComponent(EntityID entity) { return GetComponentArray<T>()->Get(entity); };

		template <typename T> ComponentSignatureIndex GetComponentSignatureID() {
			u32 typeID = typeid(T).hash_code();
			return m_ComponentSignatureIndex[typeID];
		};

		// Systems
		// -----------------------------------------------------------------

		template <typename T> void RegisterSystem() {
			u32 typeID = typeid(T).hash_code();
			System *system = new T();
			m_Systems.insert({typeID, system});
			system->InitSignature();
		};

		template <typename T> void RegisterSystem(T *system) {
			u32 typeID = typeid(T).hash_code();
			m_Systems.insert({typeID, system});
			system->InitSignature();
		};

	private:
		TQueue<EntityID> m_AvailableEntityIDs{};
		TArray<Signature, MAX_ENTITIES> m_Signatures{};
		u32 m_ActiveEntitiesCount{};

		THashMap<u32, IComponentArray *> m_ComponentArrays{};
		THashMap<u32, ComponentSignatureIndex> m_ComponentSignatureIndex{};
		ComponentSignatureIndex m_NextComponentIndex{};

		THashMap<u32, System *> m_Systems{};

		// -----------------------------------------------------------------

		void EntitySignatureChanged(EntityID entityID) {
			Signature entitySignature = m_Signatures[entityID];

			for (auto const &pair : m_Systems) {
				u32 systemTypeID = pair.first;
				System *system = pair.second;

				if ((entitySignature & system->m_Signature) == system->m_Signature) {
					// We don't have to check if its already added
					// because we are using a set
					system->m_EntitiesCache.insert(entityID);
				} else {
					system->m_EntitiesCache.erase(entityID);
				}
			}
		}

		template <typename T> ComponentArray<T> *GetComponentArray() {
			u32 typeID = typeid(T).hash_code();
			return dynamic_cast<ComponentArray<T> *>(m_ComponentArrays[typeID]);
		}
	};

} // namespace Cookie